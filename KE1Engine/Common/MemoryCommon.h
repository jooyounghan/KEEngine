#pragma once
#include "TypeCommon.h"

namespace ke
{
	CONSTEXPR_INLINE constexpr size_t _kPageThresholdSize = 4096;
	CONSTEXPR_INLINE constexpr size_t _kCachelineAlignSize = (sizeof(void*) == 8) ? 64 : 32;

	template<size_t ColumnIndex, typename T, typename... Types>
	struct GetType 
	{
		using Type = typename GetType<ColumnIndex - 1, Types...>::Type;
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
		NODISC CONSTEXPR_INLINE static constexpr T* AddressOf(T& arg) noexcept;

		template <typename T1, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t alignOf() noexcept;

		NODISC CONSTEXPR_INLINE static constexpr size_t getAlignedUp(size_t offset, size_t alignment) noexcept;

		template<size_t ColumnIndex, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getOffset() noexcept;

	private:
		template <typename T>
		NODISC CONSTEXPR_INLINE static constexpr size_t getPaddedSizeOfImpl() noexcept;
		template <typename T1, typename T2, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getPaddedSizeOfImpl() noexcept;

	public:
		template <typename ...Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getPaddedSizeOf() noexcept;

		template <typename T, typename... Types>
		NODISC CONSTEXPR_INLINE static constexpr size_t getSizeOf() noexcept;

	public:
		template <bool InitializeNull, typename ...Types>
		NODISC static void* aligendMalloc(size_t count);

		template<typename ...Types>
		static void aligendFree(void* aligned);

		template<typename T>
		static void SafeRelease(T*& ptr) noexcept;

		// TODO : 벡터 한정이므로 수정 필요
		inline static size_t CalculateTargetCapacity(const size_t targetCount, const size_t currentCapacity);
	};
}

#include "MemoryCommon.hpp"