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
        return KEMath::max(alignof(T), __STDCPP_DEFAULT_NEW_ALIGNMENT__);
    }

    template <typename T1, typename T2, typename... Ts>
    constexpr size_t KEMemory::memoryAlignOf() noexcept
    {
        constexpr size_t head = memoryAlignOf<T1>();
        constexpr size_t tail = memoryAlignOf<T2, Ts...>();
        return KEMath::max(head, tail);
    }

    template<typename T>
    constexpr size_t KEMemory::getSizeOfN(const size_t count) noexcept
    {
        return sizeof(T) * count;
    }

    template <typename T1, typename T2, typename... Ts>
    constexpr size_t KEMemory::getSizeOfN(KE_IN const size_t count) noexcept
    {
		return getSizeOfN<T1>(count) + getSizeOfN<T2, Ts...>(count);
    }


	template <typename T>
    void* KEMemory::aligendMalloc(const size_t count)
    {
        if (count == 0)
        {
            return nullptr;
        }

        constexpr size_t memoryAlign = memoryAlignOf<T>();
        size_t requestedBytes = getSizeOfN<T>(count);

        if constexpr (memoryAlign > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
        {
            if constexpr (requestedBytes >= _kPageThresholdSize)
            {
                memoryAlign = KEMath::max(memoryAlign, _kCachelineAlignSize);
            }
        }

        return _aligned_malloc(requestedBytes, memoryAlign);
    }


}
