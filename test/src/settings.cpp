#include <gtest/gtest.h>

#include <omen/settings.hpp>
#include <sstream>
#include <variant>

using omen::EngineSettings;
using omen::SettingsError;

// Ensure empty toml data succeeds
TEST(EngineSettings, emptyToml) {
  std::stringstream empty("");
  auto settings = EngineSettings::from_toml(empty);
  EXPECT_TRUE(
      std::holds_alternative<std::unique_ptr<EngineSettings>>(settings));
}

// Ensure invalid toml data fails
TEST(EngineSettings, invalidToml) {
  std::stringstream invalid("x = y");
  auto settings = EngineSettings::from_toml(invalid);
  ASSERT_TRUE(std::holds_alternative<SettingsError>(settings));
  EXPECT_EQ(std::get<1>(settings), SettingsError::Toml);
}

// Ensure valid toml sets the configuration keys
TEST(EngineSettings, validToml) {
  std::stringstream valid(
      "app_name = \"TEST_APP_NAME\"\nboot_script = \"TEST_BOOT_SCRIPT\"");
  auto settings_res = EngineSettings::from_toml(valid);
  ASSERT_TRUE(std::holds_alternative<std::unique_ptr<EngineSettings>>(settings_res));
  auto settings = std::move(std::get<0>(settings_res));
  EXPECT_EQ(settings->get_app_name(), "TEST_APP_NAME");
  EXPECT_EQ(settings->get_boot_script(), "TEST_BOOT_SCRIPT");
}
