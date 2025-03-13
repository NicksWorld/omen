#include <cstdio>
#include <cstdlib>
#include <memory>
#include <utility>
#include <variant>

#include <omen/application.h>
#include <omen/settings.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  auto engine_settings_res = omen::EngineSettings::load();
  if (auto *error = std::get_if<1>(&engine_settings_res)) {
    std::printf("Failed to load engine settings: %i\n", *error);
    std::abort();
  }
  auto engine_settings = std::move(std::get<0>(engine_settings_res));

  auto application = omen::Application::init(std::move(engine_settings));

  return 0;
}
