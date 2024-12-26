set(LUAJIT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src)
if (WIN32)
  set(LUAJIT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/lua51.lib)
else()
  set(LUAJIT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.a)
endif()

# Build LuaJIT with default settings
if (WIN32)
  add_custom_command(
    OUTPUT ${LUAJIT_LIB}
    COMMAND msvcbuild.bat
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src
    COMMENT "Building LuaJIT on Windows"
  )
else()
  add_custom_command(
    OUTPUT ${LUAJIT_LIB}
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src
    COMMENT "Building LuaJIT on Unix-like systems"
)
endif()
add_custom_target(_LuaJIT ALL DEPENDS ${LUAJIT_LIB})

# Add LuaJIT as a library
# IMPORTED GLOBAL allows it to refer to the static library built from the custom commands
add_library(LuaJIT STATIC IMPORTED GLOBAL DEPENDS ${LUAJIT_LIB})
set_target_properties(LuaJIT PROPERTIES
  IMPORTED_LOCATION "${LUAJIT_LIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${LUAJIT_INC_DIR}"
)
add_dependencies(LuaJIT _LuaJIT)
