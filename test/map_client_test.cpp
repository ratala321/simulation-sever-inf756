#include "map_client.h"

#include <gtest/gtest.h>

class MapClientTestSuite : public ::testing::Test {
};

TEST_F(MapClientTestSuite, GetAllMaps) {
	SCS::MapClient mapClient{};

	EXPECT_TRUE(mapClient.getAllMaps());
}
