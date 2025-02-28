#include "lualib.h"
#include "luacode.h"

#include <string>
#include <cstdio>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  std::string source = "print('Hello, World!')";

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  size_t bytecodeSize = 0;
  char* bytecode = luau_compile(source.c_str(), source.length(), NULL, &bytecodeSize);
  if (bytecode == nullptr) {
    std::printf("Failed to compile source\n");
    return 1;
  }
  int res = luau_load(L, "test", bytecode, bytecodeSize, 0);
  if (res != 0) {
    std::printf("Failed to load bytecode\n");
    return 1;
  }
  free(bytecode);
  res = lua_pcall(L, 0, 0, 0);
  if (res != 0) {
    std::printf("An error occured when running lua\n");
    return 1;
  }

  return 0;
}
