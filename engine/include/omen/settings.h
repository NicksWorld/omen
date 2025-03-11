#pragma once

#include <istream>
#include <memory>
#include <string_view>
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
  std::string_view app_name = "Omen Application";
  /// Path of the core script which is used as the Lua entrypoint
  std::string_view boot_script = "core/boot/boot.lua";

  /// Loads settings from the current working directory
  static SettingsResult<std::unique_ptr<EngineSettings>> load();

  /// Initializes settings based on toml values
  static SettingsResult<std::unique_ptr<EngineSettings>>
  from_toml(std::istream &stream);
};
}
