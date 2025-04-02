#pragma once

#include <istream>
#include <memory>
#include <variant>

namespace omen {
enum SettingsError { File, Toml };

/// Represents the result of a fallible settings method.
template <typename T> using SettingsResult = std::variant<T, SettingsError>;

/// Core configuration for an Omen Application
class EngineSettings {
private:
  EngineSettings() = default;

public:
  ~EngineSettings() = default;

  /// Name for the application
  const std::string &get_app_name() const { return app_name; }
  /// Path of the core script which is used as the Lua entrypoint
  const std::string &get_boot_script() const { return boot_script; }

  /// Loads settings from the current working directory
  static SettingsResult<std::unique_ptr<EngineSettings>> load();

  /// Initializes settings based on toml values
  static SettingsResult<std::unique_ptr<EngineSettings>>
  from_toml(std::istream &stream);

private:
  std::string app_name = "Omen Application";
  std::string boot_script = "core/boot/boot.lua";
};
}
