add_subdirectory(controller)
target_link_libraries(simulation_server PUBLIC controller)

add_subdirectory(lang)

add_subdirectory(serialization)
