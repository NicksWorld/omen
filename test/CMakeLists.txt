file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false src/*.h src/*.cpp)

add_executable(omen_test ${TEST_SOURCES})
target_link_libraries(omen_test PRIVATE omen_common)
target_link_libraries(omen_test PRIVATE omen_engine)

target_link_libraries(omen_test PRIVATE gtest_main)
