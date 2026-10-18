include(FetchContent)

FetchContent_Declare(
    external-googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    FIND_PACKAGE_ARGS NAMES googletest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(external-googletest)

add_executable(unit_tests
    example.cpp
)
target_link_libraries(unit_tests PRIVATE simulation_server gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)