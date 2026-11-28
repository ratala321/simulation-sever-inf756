include(FetchContent)
include(GoogleTest)

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
    integration_test.cpp
    serialization.cpp
    map_client_test.cpp
)
target_link_libraries(unit_tests PRIVATE simulation_server rpc lang serialization map_client gtest_main)

add_custom_command(TARGET unit_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENSSL_ROOT_DIR}/libcrypto-3-x64.dll"
        "${OPENSSL_ROOT_DIR}/libssl-3-x64.dll"
        $<TARGET_FILE_DIR:unit_tests>
)

gtest_discover_tests(unit_tests)