add_library(lang INTERFACE
	visitor.h
	is_instance_of.h
)

target_include_directories(lang INTERFACE .)