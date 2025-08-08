#include "MemoryCommon.h"
#include "MathCommon.h"

namespace ke
{
    template<typename T>
    constexpr T* KEMemory::AddressOf(KE_IN T& arg) noexcept
    {
        return reinterpret_cast<T*>(
            &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)
                )
            );
    }

    template <typename T>
    constexpr size_t KEMemory::memoryAlignOf() noexcept
    {
        return alignof(T);
    }

    template <typename T1, typename T2, typename... Types>
    constexpr size_t KEMemory::memoryAlignOf() noexcept
    {
        constexpr size_t head = memoryAlignOf<T1>();
        constexpr size_t tail = memoryAlignOf<T2, Types...>();
        return KEMath::max(head, tail);
    }

    constexpr size_t KEMemory::getAlignedUp(size_t value, size_t alignment) noexcept
    {
        if (alignment == 0) return value;

        if (KEMath::isPowerOf2(alignment)) 
        {
            return (value + (alignment - 1)) & ~(alignment - 1);
        }
        else 
        {
            size_t r = value % alignment;
            return r ? value + (alignment - r) : value;
        }
    }


    template<size_t Index, typename ...Types>
    constexpr size_t KEMemory::getOffset() noexcept
    {
        if constexpr (Index == 0) 
        {
            return 0;
        }
        else 
        {
			static_assert(Index < sizeof...(Types), "Index out of bounds for Types");

            using CurrentType = typename GetType<Index, Types...>::Type;
            using PrevType = typename GetType<Index - 1, Types...>::Type;

            constexpr size_t prevSize = sizeof(PrevType);
            constexpr size_t prevOffset = KEMemory::getOffset<Index - 1, Types...>();

            constexpr size_t currentOffset = prevOffset + prevSize;
            return getAlignedUp(currentOffset, alignof(CurrentType));
        }
    }

    template<typename T>
    constexpr size_t KEMemory::getSizeOfImpl() noexcept
    {
        return sizeof(T);
    }

    template<typename T1, typename T2, typename ...Types>
    constexpr size_t KEMemory::getSizeOfImpl() noexcept
    {
        return getAlignedUp(getSizeOfImpl<T2, Types...>(), alignof(T2)) + getSizeOfImpl<T1>();
    }


    template <typename ...Types>
    constexpr size_t KEMemory::getSizeOf() noexcept
    {
		constexpr size_t maxAlignment = memoryAlignOf<Types...>();
		return getAlignedUp(getSizeOfImpl<Types...>(), maxAlignment);
    }

    template <typename ...Types>
    void* KEMemory::aligendMalloc(size_t count)
    {
        if (count == 0) return nullptr;

        constexpr size_t maxAlignment = memoryAlignOf<Types...>();
        size_t requestedBytes = count * getSizeOf<Types...>();

        if constexpr (maxAlignment > __STDCPP_DEFAULT_NEW_ALIGNMENT__ && requestedBytes >= _kPageThresholdSize)
        {
            maxAlignment = KEMath::max(maxAlignment, _kCachelineAlignSize);
        }

        return _aligned_malloc(requestedBytes, maxAlignment);
    }
}
