#pragma once
#include "TypeCommon.h"

namespace ke
{
	CONSTEXPR_INLINE constexpr size_t _kPageThresholdSize = 4096;
	CONSTEXPR_INLINE constexpr size_t _kCachelineAlignSize = (sizeof(void*) == 8) ? 64 : 32;

	template<size_t Index, typename T, typename... Types>
	struct GetType 
	{
		using Type = typename GetType<Index - 1, Types...>::Type;
	};

	template<typename T, typename... Types>
	struct GetType<0, T, Types...>
	{
		using Type = T;
	};

	struct KEMemory
	{
	public:
		template<typename T>
		NODISC CONSTEXPR_INLINE static constexpr T* AddressOf(KE_IN T& arg) noexcept;

		template <typename T>
		NODISC CONSTEXPR_INLINE static constexpr size_t memoryAlignOf() noexcept;

		template <typename T1, typename T2, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t memoryAlignOf() noexcept;

		NODISC CONSTEXPR_INLINE static constexpr size_t getAlignedUp(size_t offset, size_t alignment) noexcept;

		template<size_t Index, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getOffset() noexcept;

	private:
		template <typename T>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOfImpl() noexcept;
		template <typename T1, typename T2, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOfImpl() noexcept;

	public:
		template <typename ...Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOf() noexcept;

	public:
		template <typename ...Types>
		NODISC static void* aligendMalloc(size_t count);

		NODISC static void aligendFree(KE_IN void* aligned);

		// TODO : 벡터 한정이므로 수정 필요
		NODISC static size_t CalculateTargetCapacity(KE_IN const size_t targetCount, KE_IN const size_t currentCapacity);
	};
}

#include "MemoryCommon.hpp"