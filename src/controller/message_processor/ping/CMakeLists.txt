add_library(ping OBJECT
	ping_processor.h
	ping_processor.cpp
)

target_include_directories(ping PUBLIC .)

target_link_libraries(ping PUBLIC client_datatype network_definitions network_interface rpc)
target_link_libraries(ping PRIVATE spdlog::spdlog)
