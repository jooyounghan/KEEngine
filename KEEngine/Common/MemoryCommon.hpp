#include "MemoryCommon.h"
#include "MathCommon.h"

namespace ke
{
    template<typename T>
    constexpr T* KEMemory::AddressOf(T& arg) noexcept
    {
        return reinterpret_cast<T*>(
            &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)
                )
            );
    }

    template <typename T1, typename... Types>
    constexpr size_t KEMemory::alignOf() noexcept
    {
        if constexpr (sizeof...(Types) == 0) 
        {
            return alignof(T1);
        }
        else 
        {
            constexpr size_t head = alignOf<T1>();
            constexpr size_t tail = alignOf<Types...>();
            return KEMath::max(head, tail);
        }
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


    template<size_t ColumnIndex, typename ...Types>
    constexpr size_t KEMemory::getOffset() noexcept
    {
        if constexpr (ColumnIndex == 0) 
        {
            return 0;
        }
        else 
        {
			static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for Types");

            using CurrentType = typename GetType<ColumnIndex, Types...>::Type;
            using PrevType = typename GetType<ColumnIndex - 1, Types...>::Type;

            constexpr size_t prevSize = sizeof(PrevType);
            constexpr size_t prevOffset = KEMemory::getOffset<ColumnIndex - 1, Types...>();

            constexpr size_t currentOffset = prevOffset + prevSize;
            return getAlignedUp(currentOffset, alignof(CurrentType));
        }
    }

    template<typename T>
    constexpr size_t KEMemory::getPaddedSizeOfImpl() noexcept
    {
        return sizeof(T);
    }

    template<typename T1, typename T2, typename ...Types>
    constexpr size_t KEMemory::getPaddedSizeOfImpl() noexcept
    {
        return getAlignedUp(getPaddedSizeOfImpl<T2, Types...>(), alignof(T2)) + getPaddedSizeOfImpl<T1>();
    }


    template <typename ...Types>
    constexpr size_t KEMemory::getPaddedSizeOf() noexcept
    {
		constexpr size_t maxAlignment = alignOf<Types...>();
		return getAlignedUp(getPaddedSizeOfImpl<Types...>(), maxAlignment);
    }

    template<typename T, typename ...Types>
    constexpr size_t KEMemory::getSizeOf() noexcept
    {
        if constexpr (sizeof...(Types) == 0)
        {
            return sizeof(T);
        }
        else
        {
            return sizeof(T) + getSizeOf<Types...>();
        }
    }
        
    template <bool InitializeNull, typename ...Types>
    void* KEMemory::aligendMalloc(size_t count)
    {
        if (count == 0) return nullptr;

        constexpr size_t maxAlignment = alignOf<Types...>();
        size_t requestedBytes = count * getPaddedSizeOf<Types...>();

        if constexpr (maxAlignment > __STDCPP_DEFAULT_NEW_ALIGNMENT__ && requestedBytes >= _kPageThresholdSize)
        {
            maxAlignment = KEMath::max(maxAlignment, _kCachelineAlignSize);
        }

		void* ptr = _aligned_malloc(requestedBytes, maxAlignment);

        if constexpr(InitializeNull)
        {
            if (ptr != nullptr)
            {
                memset(ptr, 0, requestedBytes);
            }
		}
        return ptr;
    }

    template<typename ...Types>
    void KEMemory::aligendFree(void* ptr)
    {
        return _aligned_free(ptr);
    }
    
    template<typename T>
    void KEMemory::SafeRelease(T*& ptr) noexcept
    {
        if (ptr != nullptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    NODISC size_t KEMemory::CalculateTargetCapacity(const size_t targetCount, const size_t currentCapacity)
    {
        if (targetCount > currentCapacity)
        {
            size_t newCapacity = targetCount + (targetCount >> 1) + (targetCount & 1);
            return (newCapacity > 0) ? newCapacity : 1u;
        }
        else
        {
            size_t shrinkThreshold = static_cast<size_t>(static_cast<float>(currentCapacity) * 0.5f);
            return (targetCount < shrinkThreshold) ? shrinkThreshold : currentCapacity;
        }
    }

}
