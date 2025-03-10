set(ENGINE_SOURCES
  application.cpp
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

target_link_libraries(omen_engine PRIVATE omen_common)
target_compile_options(omen_engine PRIVATE ${OMEN_CXX_FLAGS})
