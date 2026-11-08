option(GENERATE_ASM "Generate the assembly files when compiling" OFF)
if (${GENERATE_ASM})
	message("generating assembly")
	if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		message("for MSVC")
		add_compile_options(/FA)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message("for GNU")
		add_compile_options(-Wa -alh)
	endif()
endif()

add_subdirectory(controller)

add_subdirectory(lang)

add_subdirectory(serialization)
