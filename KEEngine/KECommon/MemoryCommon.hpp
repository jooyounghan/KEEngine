#include "MemoryCommon.h"
#include "MathCommon.h"
#include <cstdlib>

namespace ke
{
    template <class T>
    KE_INLINE NODISC constexpr size_t KEMemory::memoryAlignOf()
    { 
        return KEMath::max(alignof(T), __STDCPP_DEFAULT_NEW_ALIGNMENT__); 
    }

    template<class T>
    KE_INLINE NODISC constexpr size_t KEMemory::getSizeOfN(const size_t count)
    { 
        return sizeof(T) * count; 
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

}
