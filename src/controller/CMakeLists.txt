add_library(controller STATIC
	controller.h
	controller.cpp
)

target_include_directories(controller PUBLIC .)

add_subdirectory(client)
target_link_libraries(controller PUBLIC client_session)

add_subdirectory(controller_api)
target_link_libraries(controller PUBLIC controller_api)

add_subdirectory(rpc)

add_subdirectory(network)

target_link_libraries(controller PRIVATE spdlog::spdlog)
target_link_libraries(controller PUBLIC asio)
