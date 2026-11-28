include(FetchContent)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE "${CMAKE_SOURCE_DIR}/extern/asio/include")
target_compile_definitions(asio
    INTERFACE
    ASIO_STANDALONE
    ASIO_NO_DEPRECATED
)

FetchContent_Declare(
    external-spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.17.0
    FIND_PACKAGE_ARGS NAMES spdlog
)
FetchContent_MakeAvailable(external-spdlog)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    external-cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.67.0
    GIT_SHALLOW TRUE
    FIND_PACKAGE_ARGS NAMES cpp-httplib
)
FetchContent_MakeAvailable(external-cpp-httplib)
