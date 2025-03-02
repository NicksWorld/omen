#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <variant>

namespace omen {
  /// Represents the result of a fallible settings method.
  template <typename T>
  using SettingsResult = std::variant<T, std::string>;

  /// Core configuration for an Omen Application
  class EngineSettings {
  private:
    EngineSettings() = default;
  public:
    /// Name for the application
    std::string_view app_name = "Omen Application";
    /// Path of the core script which is used as the Lua entrypoint
    std::string_view boot_script = "core/boot/boot.lua";

    /// Loads settings from the current working directory
    static SettingsResult<std::unique_ptr<EngineSettings>> load();
  };
}
