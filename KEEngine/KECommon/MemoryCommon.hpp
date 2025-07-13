#include "MathCommon.h"

#include <new>
#include <cstdlib>
#include <cstring>

namespace ke
{
    template <class T>
    CONSTEXPR_INLINE NODISC constexpr size_t KEMemory::memoryAlignOf() noexcept
    { 
        return KEMath::max(alignof(T), __STDCPP_DEFAULT_NEW_ALIGNMENT__); 
    }

    template<class T>
    CONSTEXPR_INLINE NODISC constexpr size_t KEMemory::getSizeOfN(const size_t count) noexcept
    { 
        return sizeof(T) * count; 
    }

    inline NODISC size_t ke::KEMemory::CalculateNewSize(const size_t currentSize, const size_t newSize)
    {
        const size_t calculatedSize = currentSize + currentSize / 2;
        return calculatedSize > newSize ? calculatedSize : newSize;
    }

	template <class T>
    inline void* KEMemory::aligendMalloc(const size_t count)
    {
        if (count == 0)
        {
            return nullptr;
        }

        constexpr size_t memoryAlign = memoryAlignOf<T>();
        size_t requestedBytes = getSizeOfN<T>(count);

        if constexpr (memoryAlign > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
        {
            if constexpr (requestedBytes >= _pageThresholdSize)
            {
                memoryAlign = KEMath::max(memoryAlign, _cachelineAlignSize);
            }
        }

        return _aligned_malloc(requestedBytes, memoryAlign);
    }

    inline void KEMemory::aligendFree(void* ptr)
    {
        return _aligned_free(ptr);
    }

    template<class T>
    CONSTEXPR_INLINE NODISC constexpr T* KEMemory::AddressOf(KE_IN T& arg) noexcept
    {
        return reinterpret_cast<T*>(
            &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)
                )
            );
    }
}
