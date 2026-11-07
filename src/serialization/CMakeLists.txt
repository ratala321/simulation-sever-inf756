add_library(serialization STATIC
	serialization.h
	serialization.cpp
)

target_include_directories(serialization PUBLIC .)
target_link_libraries(serialization PUBLIC asio)
if (WIN32)
    target_link_libraries(serialization PUBLIC
        ws2_32
        wsock32
    )
endif()
