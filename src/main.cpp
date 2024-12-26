#include <lua.hpp>

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  const char *script = "print('Hello, Lua!')";

  if (luaL_loadstring(L, script) == LUA_OK) {
    if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
      lua_pop(L, lua_gettop(L));
    }
  }

  lua_close(L);
  return 0;
}
