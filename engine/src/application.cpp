#include "omen/application.hpp"

#include <memory>
#include <utility>

#include "omen/settings.hpp"

using namespace omen;

std::unique_ptr<Application>
Application::init(std::unique_ptr<EngineSettings> eng_settings) {
  std::unique_ptr<Application> app{new Application(std::move(eng_settings))};

  // TODO: More complete initialization
  return app;
}
