set(LUAJIT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src)
if (WIN32)
  set(LUAJIT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/lua51.dll)
  set(LUAJIT_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit-5.1.dll.a)
else()
  set(LUAJIT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src/libluajit.so)
endif()

# Build LuaJIT with default settings
if (WIN32 AND CMAKE_CROSSCOMPILING)
  add_custom_command(
    OUTPUT ${LUAJIT_LIB} ${LUAJIT_IMPLIB}
    COMMAND make "HOST_CC=gcc" "CROSS=\"x86_64-w64-mingw32-\"" "TARGET_SYS=Windows"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/luajit/src
    COMMENT "Crosscompiling LuaJIT for Windows"
  )
elseif (WIN32)
  add_custom_command(
    OUTPUT ${LUAJIT_LIB} ${LUAJIT_IMPLIB}
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
add_library(LuaJIT SHARED IMPORTED GLOBAL DEPENDS ${LUAJIT_LIB})
set_target_properties(LuaJIT PROPERTIES
  IMPORTED_LOCATION "${LUAJIT_LIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${LUAJIT_INC_DIR}"
)
if (DEFINED LUAJIT_IMPLIB)
  # IMPLIB is an import library for a dll
  set_target_properties(LuaJIT PROPERTIES
    IMPORTED_IMPLIB ${LUAJIT_IMPLIB}
  )
endif()
add_dependencies(LuaJIT _LuaJIT)

# Install the dll/so to the output directory
install(FILES ${LUAJIT_LIB} DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
