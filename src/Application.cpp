#include "Application.h"

#include "ComponentLocator.h"
#include "LoggingApi.h"

namespace Omen {
  bool Application::init() {
    // TODO: Initialize core systems
    m_components.bind<LoggingApi>();
    return true;
  }

  void Application::shutdown() {
    // TODO: Shutdown core systems
  }

  void Application::run() {
    if (!init()) {
      // Initialization failed, error out
      return;
    }

    m_components.getComponent<LoggingApi>()->log(LogLevel::DEBUG,
                                                 "Hello, World!");

    // TODO: Run application
    shutdown();
  }
} // namespace Omen
