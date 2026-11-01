#include "controller.h"

#include "../../rpc_message/rpc_message.h"
#include "../../rpc_message/rpc_message_trait.h"
#include "../../rpc_message/rpc_serialize.h"
#include "../../rpc_message/rpc_deserialize.h"
#include "rpc_message_body_erasure.h"

#include <gtest/gtest.h>

class ExampleTestSuite : public ::testing::Test {
};

TEST_F(ExampleTestSuite, SanityTest) {
	EXPECT_EQ(1, 1);
}

TEST_F(ExampleTestSuite, RpcMessageBodyErasure_unsafeGet)
{

	SCS::RPC::ReadBuffer buffer;
	SCS::RPC::MessageTraitVariant msgVariant{ SCS::RPC::IdSyncMessageType{} };

	auto r = SCS::RPC::deserialize(msgVariant, buffer);
	SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync> msg = r.unsafeGet<SCS::RPC::RpcMessageBody<SCS::RPC::RpcMessageType::idSync>>();
}

