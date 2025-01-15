#pragma once

#include <string_view>
#include <vector>

#include "ComponentLocator.h"

namespace Omen {
  /// Core application state and logic
  class Application {
  public:
    // Disallow moving and copying
    Application(const Application &) = delete;
    void operator=(const Application &) = delete;
    Application(Application &&) = delete;

    /// Create and prepare the application for initialization.
    Application(const std::vector<std::string_view> &argv) : m_argv(argv) {}
    ~Application() = default;

    /// Enters the main application loop. Returns on app exit.
    void run();

    /// Returns the command-line arguments given to the program.
    const std::vector<std::string_view> &argv() const { return m_argv; }

  private:
    /// Initialize core application services. Returns true on success.
    bool init();
    /// Shutdown core application services.
    void shutdown();

    const std::vector<std::string_view> m_argv;
    Omen::ComponentLocator m_components;
  };
} // namespace Omen
