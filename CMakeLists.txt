cmake_minimum_required(VERSION 3.21)

option(OMEN_TEST "Enable compilation of tests" OFF)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable additional warnings
if (UNIX)
  set(OMEN_CXX_FLAGS "-Werror" "-Wall" "-Wextra" "-Wshadow" "-Wconversion" "-pedantic" "-Wold-style-cast" "-Woverloaded-virtual" "-Wimplicit-fallthrough")
elseif (WIN32)
  set(OMEN_CXX_FLAGS "/WX" "/W4")
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

add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(launcher)

if (OMEN_TEST)
  add_subdirectory(test)
endif()
