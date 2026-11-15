add_library(network_interface INTERFACE
	socket_owner.h
)

target_include_directories(network_interface INTERFACE .)