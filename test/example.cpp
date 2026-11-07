#include "controller.h"

#include <gtest/gtest.h>

class ExampleTestSuite : public ::testing::Test {
};

TEST_F(ExampleTestSuite, SanityTest) {
	EXPECT_EQ(1, 1);
}
