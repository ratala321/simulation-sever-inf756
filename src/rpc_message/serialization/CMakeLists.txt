add_library(serialization OBJECT
	serialization.h
	serialization.cpp
)

target_include_directories(serialization PUBLIC .)
target_link_libraries(serialization PUBLIC asio)
