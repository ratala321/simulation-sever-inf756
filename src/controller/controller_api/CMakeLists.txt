add_library(controller_api OBJECT
	controller_api.h
	controller_api.cpp
)

target_include_directories(controller_api PUBLIC .)

target_link_libraries(controller_api PRIVATE asio spdlog::spdlog)