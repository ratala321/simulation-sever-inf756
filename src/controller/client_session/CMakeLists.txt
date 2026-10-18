add_library(client_session OBJECT
	client_session.h
	client_session.cpp
)

target_include_directories(client_session PUBLIC .)

target_link_libraries(client_session PRIVATE asio spdlog::spdlog)