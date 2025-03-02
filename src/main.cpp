#include <cstdio>
#include <string>
#include <variant>

#include "settings.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  auto engine_settings = omen::EngineSettings::load();
  if (auto error = std::get_if<std::string>(&engine_settings)) {
    std::printf("Failed to load engine settings: %s\n", error->c_str());
    std::abort();
  }

  return 0;
}
