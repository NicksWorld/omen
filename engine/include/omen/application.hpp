#pragma once

#include <memory>

#include "omen/settings.hpp"

namespace omen {
/// Core application construct
class Application {
private:
  Application(std::unique_ptr<EngineSettings> eng_settings)
      : engine_settings(std::move(eng_settings)) {}

public:
  /// Initialize a new application with the provided settings
  static std::unique_ptr<Application> init(std::unique_ptr<EngineSettings>);

  /// Get the engine settings used by the application
  const EngineSettings *settings() const { return engine_settings.get(); }

private:
  const std::unique_ptr<EngineSettings> engine_settings;
};
}
