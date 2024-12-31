cmake_minimum_required(VERSION 3.20)

include(ExternalProject)

# Most of the tooling configuration is contained withing the cmake presets.
# See cmake-presets(7) for more information

set(OMEN_VERSION "0.0.0")

project(omen VERSION 0.0.0 LANGUAGES CXX)

# Output all artifacts to a directory named "output"
set(OMEN_OUTPUT_DIR "$<1:${CMAKE_BINARY_DIR}/output>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OMEN_OUTPUT_DIR})

# External dependencies
add_subdirectory(external)

# Sources for the engine exectuable, located in src/ for now
set(ENGINE_SOURCES
  main.cpp
)
list(TRANSFORM ENGINE_SOURCES PREPEND "src/")

add_executable(omen_engine ${ENGINE_SOURCES})
set_target_properties(
  omen_engine
  PROPERTIES
  OUTPUT_NAME omen
)
target_link_libraries(omen_engine PRIVATE LuaJIT)
