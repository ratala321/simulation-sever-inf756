add_library(lang STATIC
	empty.cpp
	visitor.h
	is_instance_of.h
)

target_include_directories(lang PUBLIC .)