#include "map_client.h"

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace SCS
{

struct MapClient::Impl
{
	static constexpr int mapServerPort = 5000;

	Impl() : client{ "127.0.0.1", 5000}
	{}

	httplib::Client client;
};

MapClient::MapClient() : pimpl{ std::make_unique<MapClient::Impl>() }
{
	if (!pimpl || !pimpl->client.is_valid())
	{
		throw failed_to_start_client{};
	}
}

MapClient::~MapClient()
{}

bool MapClient::getAllMaps()
{
	using json = nlohmann::json;

	if (auto res = pimpl->client.Get("/")) {
		spdlog::info("Get route `/` of map server, response status : `{}`", res->status);
		if (res->status == httplib::OK_200)
		{
			auto mapJson = json::parse(res->body);
			return true;
		}
	}
	else
	{
		spdlog::warn("Can't get all maps: `{}`", httplib::to_string(res.error()));
	}

	return false;
}

};
