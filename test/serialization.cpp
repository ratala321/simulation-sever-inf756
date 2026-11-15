#include "serialization.h"
#include "rpc_message_type.h"

#include <gtest/gtest.h>

class SerializationTestSuite : public ::testing::Test
{
};

TEST_F(SerializationTestSuite, SerializationLoopOfSingle_uint8)
{
	uint8_t value = 0;
	uint8_t startBuffer[1];
	SCS::Serialization::serializeRaw(startBuffer, value);

	uint8_t result;
	SCS::Serialization::deserializeRaw(startBuffer, result);

	EXPECT_EQ(value, result);
}

TEST_F(SerializationTestSuite, SerializationLoopOfMultipleTypesOf_uint)
{
	uint8_t value1 = 23;
	uint16_t value2 = 11;
	uint32_t value3 = 43;
	uint8_t startBuffer[sizeof(value1) + sizeof(value2) + sizeof(value3)];
	auto temp = SCS::Serialization::serializeRaw(startBuffer, value1);
	temp = SCS::Serialization::serializeRaw(temp, value2);
	SCS::Serialization::serializeRaw(temp, value3);

	uint8_t result1;
	uint16_t result2;
	uint32_t result3;
	SCS::Serialization::deserializeRaw(startBuffer, result1);
	SCS::Serialization::deserializeRaw(startBuffer + sizeof(result1), result2);
	SCS::Serialization::deserializeRaw(startBuffer + sizeof(result1) + sizeof(result2), result3);

	EXPECT_EQ(value1, result1);
	EXPECT_EQ(value2, result2);
	EXPECT_EQ(value3, result3);
}

TEST_F(SerializationTestSuite, SerializationOfStaticCastRpcMessageType)
{
	using RawEnumType = std::underlying_type_t<SCS::RPC::RpcMessageType>;

	static constexpr size_t sizeOfBuffer = sizeof(SCS::RPC::RpcMessageType::ping);
	uint8_t buffer[sizeOfBuffer];
	SCS::Serialization::serializeRaw(buffer, static_cast<RawEnumType>(SCS::RPC::RpcMessageType::ping));

	RawEnumType result;
	SCS::Serialization::deserializeRaw(buffer, result);

	EXPECT_EQ(SCS::RPC::RpcMessageType::ping, static_cast<SCS::RPC::RpcMessageType>(result));
}
