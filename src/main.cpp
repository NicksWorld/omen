#include <string_view>
#include <vector>

#include "Application.h"

int main(int argc, char *argv[]) {
  const std::vector<std::string_view> args(argv, argv + argc);

  Omen::Application app(args);
  app.run();

  return 0;
}
