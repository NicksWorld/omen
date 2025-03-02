#include "settings.h"

#include <filesystem>
#include <fstream>
#include <memory>

#include <toml++/toml.hpp>

using namespace omen;

// If node contains a value of the specified type, loads the value into field.
template <typename T>
void populate_setting(const toml::node_view<toml::node> &node, T &field) {
  if (auto res = node.value<T>()) {
    field = *res;
  }
}

SettingsResult<std::unique_ptr<EngineSettings>> EngineSettings::load() {
  std::filesystem::path toml_path("engine.toml");

  // Open the file
  std::ifstream toml_stream(toml_path);
  if (toml_stream.fail()) {
    return "Failed to open file";
  }

  // Parse the file
  toml::parse_result settings_raw = toml::parse(toml_stream);
  if (!settings_raw) {
    return "Failed to parse toml";
  }

  std::unique_ptr<EngineSettings> engine_settings{new EngineSettings()};

  // Populate settings fields
  populate_setting(settings_raw["app_name"], engine_settings->app_name);
  populate_setting(settings_raw["boot_script"], engine_settings->boot_script);

  return engine_settings;
}
