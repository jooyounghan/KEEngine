#pragma once
#include "TypeCommon.h"

namespace ke
{
	KE_INLINE constexpr size_t _pageThresholdSize = 4096;
	KE_INLINE constexpr size_t _cachelineAlignSize = 32;

	struct KEMemory
	{
		template <class T>
		KE_INLINE NODISC static constexpr size_t memoryAlignOf();

		template <class T>
		KE_INLINE NODISC static constexpr size_t getSizeOfN(const size_t count);

		template <class T>
		KE_INLINE NODISC static void* aligendMalloc(const size_t count);
	};
}

#include "MemoryCommon.hpp"