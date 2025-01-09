#pragma once

#include <algorithm>
#include <deque>
#include <format>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace Omen {
  /**
   * @brief Implementation of the service locator pattern for managing
   * components.
   *
   * The component locator is in charge of managing dependencies between
   * components. Components may be either default constructible or take a
   * reference to the ComponentLocator in order to request their dependencies.
   *
   * @note The component locator is thread-safe.
   *
   * @note Components must be bound via ComponentLocator::bind before
   * being requested by ComponentLocator::getComponent
   */
  class ComponentLocator {
  public:
    ComponentLocator() = default;
    ~ComponentLocator() = default;

    /**
     * Register a component to be accessible via
     * ComponentLocator::getComponent
     *
     * @tparam Interface The interface used to interact with the component.
     * @tparam Impl The implementation of the interface to be used. This is the
     * same as the Interface unless specified.
     *
     * @note The component is lazily constructed upon first request.
     *
     * @throws runtime_error upon duplicate registrations of an interface.
     */
    template <typename Interface, typename Impl = Interface> void bind() {
      const std::scoped_lock lck(m_lock);
      auto idx = std::type_index(typeid(Interface));

      // Ensure another implementation isn't already registered
      if (m_components.contains(idx)) {
        throw std::runtime_error(
            std::format("An implementation for the component {} already exists",
                        typeid(Interface).name()));
      }

      m_components.insert(
          {idx, {createFactory<Impl>(), std::shared_ptr<void>()}});
    }

    /**
     * Obtain a reference to the specified component Interface.
     *
     * References are guarenteed to refer to the same instance each time
     * requested.
     *
     * @tparam Interface The component interface that is requested.
     *
     * @note To make an interface accessible, it must first be bound via
     * ComponentLocator::bind.
     *
     * @throws runtime_error upon detection of a dependency cycle.
     * @throws ... if initializing the component results in an exception.
     */
    template <typename Interface> std::shared_ptr<Interface> getComponent() {
      const std::scoped_lock lck(m_lock);
      auto idx = std::type_index(typeid(Interface));

      auto interface = m_components.find(idx);

      if (interface == m_components.end()) {
        // Interface has no registered factory or instance
        throw std::runtime_error(
            std::format("No bound implementation to produce component {}",
                        typeid(Interface).name()));
      }
      if (interface != m_components.end() && interface->second.instance) {
        // Interface is already initialized
        return std::static_pointer_cast<Interface>(interface->second.instance);
      }
      // Interface factory exists, but has not yet been constructed.

      // Determine if the interface is being constructed actively.
      // This is caused by a cyclic dependency and would cause an infinte loop.
      auto firstOccurance = std::find(m_initializingStack.begin(),
                                      m_initializingStack.end(), idx);
      if (firstOccurance != m_initializingStack.end()) {
        throw std::runtime_error("Cyclic dependency detected");
      }

      m_initializingStack.push_back(idx);
      try {
        // The factory may throw an exception from a user-defined constructor.
        auto newInterface = interface->second.factory(*this);
        m_initializingStack.pop_back();
        return std::static_pointer_cast<Interface>(newInterface);
      } catch (...) {
        // Maintain a usable state so the caller can recover gracefully.
        m_initializingStack.pop_back();
        throw;
      }
    }

  private:
    // Creates a factory function for the given component.
    template <typename Impl>
    std::function<std::shared_ptr<void>(ComponentLocator &)> createFactory() {
      if constexpr (std::is_constructible_v<Impl, ComponentLocator &>) {
        return
            [](ComponentLocator &loc) { return std::make_shared<Impl>(loc); };
      } else if constexpr (std::is_constructible_v<Impl>) {
        return []([[maybe_unused]] ComponentLocator &loc) {
          return std::make_shared<Impl>();
        };
      } else {
        static_assert(false, "Component impl is not constructible with "
                             "ComponentLocator& or default constructible.");
      }
    }

    struct Component {
      // Factory method for constructing the component.
      std::function<std::shared_ptr<void>(ComponentLocator &)> factory;
      // Pointer to the component, nullptr if not yet constructed.
      std::shared_ptr<void> instance;
    };

    // Unified map for factories and constructed components
    std::unordered_map<std::type_index, Component> m_components;

    // Stack used for detecting when a dependency cycle is encountered.
    std::deque<std::type_index> m_initializingStack;

    // Used to protect the internals from being read or modified concurrently.
    // A recursive mutex is used as the locator may be used during the
    // initialization of a component.
    std::recursive_mutex m_lock;
  };
} // namespace Omen
