cmake_minimum_required(VERSION 3.26)
project(simulation_server CXX)
include(CTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/build_system/fetch_dependencies.cmake)

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

target_link_libraries(simulation_server PRIVATE asio)
target_link_libraries(simulation_server PRIVATE spdlog::spdlog)
