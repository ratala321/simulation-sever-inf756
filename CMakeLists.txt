cmake_minimum_required(VERSION 3.26)
project(simulation_server CXX)
include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
endif()

add_library(simulation_server STATIC main.cpp)

add_executable(simulation_server_executable bootstrap.cpp)
target_link_libraries(simulation_server_executable PRIVATE simulation_server)

add_subdirectory(src bin)
target_link_libraries(simulation_server PUBLIC controller)

add_subdirectory(test)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/extern/asio/include")
target_compile_definitions(asio
    INTERFACE
    ASIO_STANDALONE
    ASIO_NO_DEPRECATED
)
target_link_libraries(simulation_server PRIVATE asio)

include(FetchContent)
FetchContent_Declare(
    external-spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.17.0
    FIND_PACKAGE_ARGS NAMES spdlog
)
FetchContent_MakeAvailable(external-spdlog)

target_include_directories(simulation_server PRIVATE INTERFACE_INCLUDE_DIRECTORIES)
target_link_libraries(simulation_server PRIVATE spdlog::spdlog)
