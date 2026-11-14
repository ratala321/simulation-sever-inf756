add_library(message_processor STATIC
	empty.cpp
)

target_include_directories(message_processor PUBLIC .)

add_subdirectory(id_sync)
add_subdirectory(ping)
target_link_libraries(message_processor PUBLIC
	id_sync
	ping
)
