#pragma once
#include "UtilityCommon.h"

namespace ke
{
	using byte = unsigned char;
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	using int8 = char;
	using int16 = short;
	using int32 = int;
	using int64 = long long;

	using KEBufferOffset = size_t;

	struct KELimit
	{
		template<typename T>
		CONSTEXPR_INLINE static constexpr T getMax();

		template<typename T>
		CONSTEXPR_INLINE static constexpr T getMin();
	};
}

#define INVALID_INDEX(type) KELimit::getMax<type>()

#include "TypeCommon.hpp"