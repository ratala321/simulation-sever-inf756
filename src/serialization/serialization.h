#ifndef SCS_SERIALIZATION
#define SCS_SERIALIZATION

#include <asio/detail/socket_ops.hpp>

#include <algorithm>
#include <bit>
#include <concepts>
#include <type_traits>

namespace SCS::Serialization
{

template<class T>
concept Int8Normalizable = requires(T arg)
{
	requires std::is_integral_v<T> && sizeof(T) == 1;
};

template<class T>
concept Int16Normalizable = requires(T arg)
{
	requires std::is_integral_v<T> && sizeof(T) == 2;
};

template<class T>
concept Int32Normalizable = requires(T arg)
{
	requires std::is_integral_v<T> && sizeof(T) == 4;
};

template<class T>
concept IntNormalizable = requires(T arg)
{
	requires Int8Normalizable<T> ||
		Int16Normalizable<T> ||
		Int32Normalizable<T>;
};

template <Int8Normalizable T>
T normalize(T arg) { return arg; }

template <Int16Normalizable T>
T normalize(T arg) { return htons(arg); }

template <Int32Normalizable T>
T normalize(T arg) { return htonl(arg); }

template <IntNormalizable T>
unsigned char* serializeRaw(unsigned char* dest, T f)
{
	T n = normalize(f);
	auto deb = std::bit_cast<unsigned char*>(&n);
	auto fin = deb + sizeof(n);
	std::copy(deb, fin, dest);

	return dest + sizeof(n);
}

template <Int8Normalizable T>
T denormalize(T arg) { return arg; }

template <Int16Normalizable T>
T denormalize(T arg) { return ntohs(arg); }

template <Int32Normalizable T>
T denormalize(T arg) { return ntohl(arg); }

template <IntNormalizable T>
const unsigned char* deserializeRaw(const unsigned char* src, T& n)
{
	std::copy(src, src + sizeof(n), std::bit_cast<unsigned char*>(&n));

	n = denormalize(n);

	return src + sizeof(n);
}

};

#endif // !SCS_SERIALIZATION
