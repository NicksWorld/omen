set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(LUAU_BUILD_CLI OFF)
set(LUAU_BUILD_TESTS OFF)
set(LUAU_BUILD_WEB OFF)
set(LUAU_WERROR OFF)
set(LUAU_EXTERN_C ON)

add_subdirectory(luau)
