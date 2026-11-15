add_library(id_sync OBJECT
	id_sync_processor.h
	id_sync_processor.cpp
)

target_include_directories(id_sync PUBLIC .)

target_link_libraries(id_sync PUBLIC client_datatype network_definitions network_interface rpc)
target_link_libraries(id_sync PRIVATE spdlog::spdlog)
