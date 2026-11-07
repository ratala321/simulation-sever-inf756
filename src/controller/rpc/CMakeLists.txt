add_library(rpc STATIC empty.cpp)

add_subdirectory(rpc_message)
target_link_libraries(rpc PUBLIC rpc_message)

add_subdirectory(rpc_serialization)
target_link_libraries(rpc PUBLIC rpc_serialization)