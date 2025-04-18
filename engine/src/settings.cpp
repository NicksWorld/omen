#include "omen/settings.hpp"

#include <filesystem>
#include <fstream>
#include <istream>
#include <memory>

#include <toml++/toml.hpp>

using namespace omen;

namespace {
// If node contains a value of the specified type, loads the value into field.
template <typename T>
void populate_setting(const toml::node_view<toml::node> &node, T &field) {
  if (auto res = node.value<T>()) {
    field = *res;
  }
}
}

SettingsResult<std::unique_ptr<EngineSettings>> EngineSettings::load() {
  const std::filesystem::path toml_path("engine.toml");

  // Open the file
  std::ifstream toml_stream(toml_path);
  if (toml_stream.fail()) {
    return SettingsError::File;
  }

  return from_toml(toml_stream);
}

SettingsResult<std::unique_ptr<EngineSettings>>
EngineSettings::from_toml(std::istream &stream) {
  // Parse the file
  std::optional<toml::parse_result> settings_res;
  try {
    settings_res = toml::parse(stream);
  } catch (...) {
    return SettingsError::Toml;
  }
  auto settings_raw = settings_res.value();

  std::unique_ptr<EngineSettings> engine_settings{new EngineSettings()};

  // Populate settings fields
  populate_setting(settings_raw["app_name"], engine_settings->app_name);
  populate_setting(settings_raw["boot_script"], engine_settings->boot_script);

  return engine_settings;
}
