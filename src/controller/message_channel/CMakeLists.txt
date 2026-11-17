add_library(message_channel INTERFACE
	message_channel.h
)

target_include_directories(message_channel INTERFACE .)

target_link_libraries(message_channel INTERFACE asio rpc)