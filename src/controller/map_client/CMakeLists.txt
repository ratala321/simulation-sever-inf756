add_library(map_client STATIC
	map_client.h
	map_client.cpp
)

target_include_directories(map_client PUBLIC .)

target_link_libraries(map_client PRIVATE httplib::httplib nlohmann_json::nlohmann_json spdlog::spdlog)