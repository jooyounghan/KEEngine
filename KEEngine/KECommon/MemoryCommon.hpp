#include "MemoryCommon.h"
#include "MathCommon.h"

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


	template <class T>
    inline NODISC void* KEMemory::aligendMalloc(const size_t count)
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
