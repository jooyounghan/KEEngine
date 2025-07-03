#include "PoolAllocator.h"
#include "MemoryCommon.h"

namespace ke
{
    template<typename T, size_t PoolingCount>
    PoolAllocatorImpl<T, PoolingCount, true>::PoolAllocatorImpl()
    {
        static_assert(false, "1");
    }

    template<typename T, size_t PoolingCount>
    PoolAllocatorImpl<T, PoolingCount, true>::~PoolAllocatorImpl()
    {
    }

    template<typename T, size_t PoolingCount>
    PoolAllocatorImpl<T, PoolingCount, false>::PoolAllocatorImpl()
    {
        static_assert(false, "2");
    }

    template<typename T, size_t PoolingCount>
    PoolAllocatorImpl<T, PoolingCount, false>::~PoolAllocatorImpl()
    {
    }

    template<typename T, size_t PoolingCount>
    void* PoolAllocatorImpl<T, PoolingCount, true>::allocateImpl(KE_IN const size_t count)
    {
        return nullptr;
    }

    template<typename T, size_t PoolingCount>
    void PoolAllocatorImpl<T, PoolingCount, true>::deallocateImpl(KE_IN void* ptr, KE_IN const size_t count)
    {
    }

    template<typename T, size_t PoolingCount>
    void* PoolAllocatorImpl<T, PoolingCount, false>::allocateImpl(KE_IN const size_t count)
    {
        return nullptr;
    }

    template<typename T, size_t PoolingCount>
    void PoolAllocatorImpl<T, PoolingCount, false>::deallocateImpl(KE_IN void* ptr, KE_IN const size_t count)
    {
    }

    template<typename T, size_t PoolingCount>
    void* PoolAllocator<T, PoolingCount>::allocate(KE_IN const size_t count)
    {
		return _poolAllocatorImpl.allocateImpl(count);
    }

    template<typename T, size_t PoolingCount>
    void PoolAllocator<T, PoolingCount>::deallocate(KE_IN void* ptr, KE_IN const size_t count)
    {
        return _poolAllocatorImpl.deallocateImpl(ptr, count);
    }
}


