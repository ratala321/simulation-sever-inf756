add_library(rpc_message INTERFACE
	rpc_message_buffer.h
	rpc_message_type.h
	rpc_message_header.h
)

target_include_directories(rpc_message INTERFACE .)


add_subdirectory(body)
target_link_libraries(rpc_message INTERFACE rpc_message_body)


target_link_libraries(rpc_message INTERFACE client_datatype)
