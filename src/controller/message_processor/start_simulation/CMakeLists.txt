add_library(start_simulation OBJECT
	start_simulation_processor.h
	start_simulation_processor.cpp
)

target_include_directories(start_simulation PUBLIC .)

target_link_libraries(start_simulation PUBLIC client_datatype network_definitions network_interface rpc)
target_link_libraries(start_simulation PRIVATE spdlog::spdlog simulation_manager)
