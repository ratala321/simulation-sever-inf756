add_library(message_processor STATIC
	empty.cpp
	all_message_processor.h
)

target_include_directories(message_processor PUBLIC .)

add_subdirectory(id_sync)
add_subdirectory(ping)
add_subdirectory(start_simulation)
target_link_libraries(message_processor PUBLIC
	id_sync
	ping
	start_simulation
)
