cmake_minimum_required(VERSION 3.21)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable additional warnings and disable exceptions
if (UNIX)
  set(OMEN_CXX_FLAGS "-Werror" "-Wall" "-Wextra" "-Wshadow" "-Wconversion" "-pedantic" "-Wold-style-cast" "-Woverloaded-virtual" "-Wimplicit-fallthrough" "-fno-exceptions")
elseif (WIN32)
  set(OMEN_CXX_FLAGS "/WX" "/W4" "/EHsc")
else()
  set(OMEN_CXX_FLAGS "")
endif()

set(OMEN_VERSION "0.0.0")

find_program(CCACHE_EXECUTABLE "ccache")
if(CCACHE_EXECUTABLE)
  message(STATUS "Using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
  set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
endif()

set(OMEN_OUTPUT_DIR "$<1:${CMAKE_BINARY_DIR}/out>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})

add_subdirectory(external)

project(omen VERSION ${OMEN_VERSION} LANGUAGES CXX)

set(ENGINE_SOURCES
  main.cpp
  settings.cpp
)
list(TRANSFORM ENGINE_SOURCES PREPEND "src/")

add_executable(omen_engine ${ENGINE_SOURCES})
set_target_properties(
  omen_engine
  PROPERTIES
  OUTPUT_NAME omen
)
target_link_libraries(omen_engine PRIVATE Luau.Compiler Luau.VM)

target_link_libraries(omen_engine PRIVATE tomlplusplus::tomlplusplus)
add_compile_definitions(omen_engine PRIVATE TOML_EXCEPTIONS=0)

target_compile_options(omen_engine PRIVATE ${OMEN_CXX_FLAGS})
