add_library(rpc_message OBJECT
	rpc_message.h
	rpc_message_buffer.h
	rpc_message_type.h
	rpc_message_body.h
)
set_target_properties(rpc_message PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(rpc_message PUBLIC .)

add_subdirectory(serialization)
target_link_libraries(rpc_message PRIVATE serialization)
