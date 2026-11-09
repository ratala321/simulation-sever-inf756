add_library(controller STATIC
	controller.h
	controller.cpp
 "message_queue/message_queue.h" "message_queue/message_queue.cpp" "network/network_definitions.h")

target_include_directories(controller PUBLIC .)

add_subdirectory(client)
target_link_libraries(controller PUBLIC client_session)

add_subdirectory(controller_api)
target_link_libraries(controller PUBLIC controller_api)

add_subdirectory(rpc)

add_subdirectory(message_processor)
add_subdirectory(message_queue)

add_subdirectory(network)

target_link_libraries(controller PRIVATE spdlog::spdlog)
target_link_libraries(controller PUBLIC asio)
