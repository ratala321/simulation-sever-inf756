add_library(client_session OBJECT
	client_session.h
	client_session.cpp
)

target_include_directories(client_session PUBLIC .)

target_link_libraries(client_session PUBLIC client_datatype network_definitions network_interface)
target_link_libraries(client_session PRIVATE rpc message_dispatcher)

target_link_libraries(client_session PRIVATE asio spdlog::spdlog)
