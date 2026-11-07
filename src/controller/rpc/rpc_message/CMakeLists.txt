add_library(rpc_message INTERFACE
	rpc_message_buffer.h
	rpc_message_type.h
	rpc_message_body.h
)

target_include_directories(rpc_message INTERFACE .)

target_link_libraries(rpc_message INTERFACE client_datatype)
