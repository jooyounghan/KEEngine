#pragma once
#include "TypeCommon.h"

namespace ke
{
	CONSTEXPR_INLINE constexpr size_t _pageThresholdSize = 4096;
	CONSTEXPR_INLINE constexpr size_t _cachelineAlignSize = 32;

	struct KEMemory
	{
		template <class T>
		CONSTEXPR_INLINE NODISC static constexpr size_t memoryAlignOf() noexcept;

		template <class T>
		CONSTEXPR_INLINE NODISC static constexpr size_t getSizeOfN(KE_IN const size_t count) noexcept;


		NODISC static size_t CalculateExpandCapacity(const size_t usedCount, const size_t capacity);
		NODISC static size_t CalculateShrinkCapacity(const size_t usedCount, const size_t capacity);

		template <class T>
		NODISC static void* aligendMalloc(KE_IN const size_t count);

		NODISC static void aligendFree(KE_IN void* aligned);

		template<class T>
		CONSTEXPR_INLINE NODISC static constexpr T* AddressOf(KE_IN T& arg) noexcept;
	};
}

#include "MemoryCommon.hpp"