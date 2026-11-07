add_library(rpc_serialization OBJECT
	rpc_deserialize.h
	rpc_deserialize.cpp
	rpc_serialize.h
	rpc_serialize.cpp
)

target_include_directories(rpc_serialization PUBLIC .)

target_link_libraries(rpc_serialization PUBLIC rpc_message)
target_link_libraries(rpc_serialization PRIVATE serialization)
