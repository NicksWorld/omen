#pragma once

#include <cassert>
#include <format>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace Omen {
  /// Structure for managing the initialization of engine components.
  ///
  /// Components are created lazily upon first request via a getComponent call.
  class ComponentLocator {
  public:
    ComponentLocator() = default;
    ~ComponentLocator() = default;

    // Concept determining if ctor(ComponentLocator&) is available.
    template <typename Interface>
    using construct_use_locator =
        std::is_constructible<Interface, ComponentLocator &>;
    // Concept determining if ctor() is available.
    template <typename Interface>
    using construct_use_default = std::is_constructible<Interface>;

    /// Make Component available as a component.
    template <typename Component> void bind() {
      // There is no seperate interface, so they are the same.
      this->bind<Component, Component>();
    }

    /// Make Interface available as a component, via the implementation Impl.
    template <typename Interface, typename Impl> void bind() {
      static_assert(construct_use_default<Interface>::value ||
                        construct_use_locator<Interface>::value,
                    "Cannot bind component, Impl is not default constructible "
                    "or constructible with ComponentLocator&");

      const std::scoped_lock lck(m_lock);
      auto idx = std::type_index(typeid(Interface));

      // Ensure another implementation isn't already registered
      if (m_componentFactories.contains(idx)) {
        throw std::runtime_error(
            std::format("An implementation for the component {} already exists",
                        typeid(Interface).name()));
      }

      m_componentFactories.insert({idx, createFactory<Impl>()});
    }

    /// Obtain a shared_ptr to the specified Interface.
    ///
    /// Creates the component if not already initialized.
    template <typename Interface> std::shared_ptr<Interface> getComponent() {
      const std::scoped_lock lck(m_lock);
      auto idx = std::type_index(typeid(Interface));
      auto interface = m_components.find(idx);
      if (interface != m_components.end()) {
        // Interface is already initialized
        return std::static_pointer_cast<Interface>(interface->second);
      }

      // Construct the interface
      auto newInterface = createComponent<Interface>();
      m_components.insert({idx, newInterface});
      return newInterface;
    }

  private:
    // Creates a factory for the Component
    template <typename Impl>
    std::function<std::shared_ptr<void>(ComponentLocator &)> createFactory()
      requires construct_use_locator<Impl>::value
    {
      return [](ComponentLocator &loc) { return std::make_shared<Impl>(loc); };
    }

    template <typename Impl>
    std::function<std::shared_ptr<void>(ComponentLocator &)> createFactory()
      requires construct_use_default<Impl>::value &&
               (!construct_use_locator<Impl>::value)
    {
      return []([[maybe_unused]] ComponentLocator &loc) {
        return std::make_shared<Impl>();
      };
    }

    /// Constructs a Component that takes ComponentLocator& in the constructor.
    template <typename Interface> std::shared_ptr<Interface> createComponent() {
      auto interfaceFactory =
          m_componentFactories.find(std::type_index(typeid(Interface)));

      // Ensure a factory is available to produce the interface
      if (interfaceFactory == m_componentFactories.end()) {
        throw std::runtime_error(
            std::format("No bound implementation to produce component {}",
                        typeid(Interface).name()));
      }

      return std::static_pointer_cast<Interface>(
          interfaceFactory->second(*this));
    }

    // Maps storing the components and the functions used to create them.
    std::unordered_map<std::type_index, std::shared_ptr<void>> m_components;
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<void>(ComponentLocator &)>>
        m_componentFactories;

    // Used to protect the internals from being read or modified concurrently.
    // A recursive mutex is used as the locator may be used during the
    // initialization of a component.
    std::recursive_mutex m_lock;
  };
} // namespace Omen
