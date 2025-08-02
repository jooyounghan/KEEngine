#pragma once
#include "TypeCommon.h"

namespace ke
{
	CONSTEXPR_INLINE constexpr size_t _kPageThresholdSize = 4096;
	CONSTEXPR_INLINE constexpr size_t _kCachelineAlignSize = 32;

	struct KEMemory
	{
		template<typename T>
		NODISC CONSTEXPR_INLINE static constexpr T* AddressOf(KE_IN T& arg) noexcept;

		template <typename T>
		NODISC CONSTEXPR_INLINE static constexpr size_t memoryAlignOf() noexcept;

		template <typename T1, typename T2, typename... Ts>
		NODISC CONSTEXPR_INLINE static constexpr size_t memoryAlignOf() noexcept;

		template <typename T>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOfN(KE_IN const size_t count) noexcept;

		template <typename T1, typename T2, typename... Ts>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOfN(KE_IN const size_t count) noexcept;

		// TODO : 벡터 한정이므로 수정 필요
		NODISC static size_t CalculateTargetCapacity(KE_IN const size_t targetCount, KE_IN const size_t currentCapacity);

		template <typename T>
		NODISC static void* aligendMalloc(KE_IN const size_t count);

		NODISC static void aligendFree(KE_IN void* aligned);


		//struct AlignedLayout<T, Ts...> {
		//	static constexpr size_t align = 
		//	static constexpr size_t size = ((AlignedLayout<Ts...>::size + alignof(T) - 1) / alignof(T)) * alignof(T) + sizeof(T);
		//};
	};
}

#include "MemoryCommon.hpp"