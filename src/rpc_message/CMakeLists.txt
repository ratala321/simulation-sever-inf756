add_library(rpc_message OBJECT
	empty.cpp
	rpc_message.h
	rpc_message_buffer.h
	rpc_message_type.h
	rpc_message_body.h
	rpc_message_body_erasure.h
	rpc_message_trait.h
	rpc_deserialize.h
	rpc_serialize.h
)

target_include_directories(rpc_message PUBLIC .)

add_subdirectory(serialization)
target_link_libraries(rpc_message PRIVATE serialization)
