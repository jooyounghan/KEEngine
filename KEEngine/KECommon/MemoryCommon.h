#pragma once
#include "TypeCommon.h"

namespace ke
{
	CONSTEXPR_INLINE constexpr size_t _pageThresholdSize = 4096;
	CONSTEXPR_INLINE constexpr size_t _cachelineAlignSize = 32;

	struct KEMemory
	{
		template <class T>
		CONSTEXPR_INLINE NODISC static constexpr size_t memoryAlignOf();

		template <class T>
		CONSTEXPR_INLINE NODISC static constexpr size_t getSizeOfN(const size_t count);

		template <class T>
		NODISC static void* aligendMalloc(const size_t count);

		NODISC static void aligendFree(void* aligned);

	};
}

#include "MemoryCommon.hpp"