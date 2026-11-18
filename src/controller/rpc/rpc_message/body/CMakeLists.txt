add_library(rpc_message_body INTERFACE
	rpc_message_body.h
	request_body.h
	response_body.h
)

target_include_directories(rpc_message_body INTERFACE .)

target_link_libraries(rpc_message_body INTERFACE client_datatype)
