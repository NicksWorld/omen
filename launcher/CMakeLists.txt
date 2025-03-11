set(LAUNCHER_SOURCES
  main.cpp
)

list(TRANSFORM LAUNCHER_SOURCES PREPEND "src/")

add_executable(omen_launcher ${LAUNCHER_SOURCES})
set_target_properties(
  omen_launcher
  PROPERTIES
  OUTPUT_NAME omen
)
target_link_libraries(omen_launcher PRIVATE omen_engine)
target_compile_options(omen_launcher PRIVATE ${OMEN_CXX_FLAGS})
