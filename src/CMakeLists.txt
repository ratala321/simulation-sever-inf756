option(GENERATE_ASM "Generate the assembly files when compiling" OFF)
if (GENERATE_ASM AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/FA)
endif()

add_subdirectory(controller)
target_link_libraries(simulation_server PUBLIC controller)

add_subdirectory(lang)

add_subdirectory(serialization)
