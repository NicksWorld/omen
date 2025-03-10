set(COMMON_SOURCES
  hash.cpp
)

list(TRANSFORM COMMON_SOURCES PREPEND "src/")

# NOTE: If the library grows substantially, consider moving to a shared object
add_library(omen_common STATIC ${COMMON_SOURCES})
target_include_directories(omen_common PUBLIC include)

target_compile_options(omen_common PRIVATE ${OMEN_CXX_FLAGS})
