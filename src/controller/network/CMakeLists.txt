add_library(network_definitions INTERFACE
	network_definitions.h
)

target_include_directories(network_definitions INTERFACE .)

add_subdirectory(network_interface)

target_link_libraries(network_definitions INTERFACE asio)