add_library(client_session OBJECT
	client_session.h
	client_session.cpp
)

target_include_directories(client_session PUBLIC .)

target_link_libraries(client_session PUBLIC client_datatype network_defintions)
target_link_libraries(client_session PRIVATE rpc message_queue)

target_link_libraries(client_session PUBLIC asio)
target_link_libraries(client_session PRIVATE spdlog::spdlog)
