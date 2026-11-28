#ifndef SCS_MAP_CLIENT
#define SCS_MAP_CLIENT

#include <memory>

namespace SCS
{

struct failed_to_start_client {};

class MapClient
{
public:
	MapClient();
	~MapClient();

	bool getAllMaps();

private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};

};

#endif // !SCS_MAP_CLIENT