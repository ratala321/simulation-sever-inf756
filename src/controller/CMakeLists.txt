add_library(controller OBJECT
	controller.h
	controller.cpp
)

target_include_directories(controller PUBLIC .)

add_subdirectory(client_session)
target_link_libraries(simulation_server PRIVATE client_session)

target_link_libraries(controller PRIVATE asio spdlog::spdlog)