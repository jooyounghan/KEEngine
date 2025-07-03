#pragma once
#include "IMemoryAllocator.h"

namespace ke
{
    template <typename T, size_t PoolingCount, bool CanEmbedFreeList>
    class PoolAllocatorImpl;

    template <typename T, size_t PoolingCount>
    class PoolAllocatorImpl<T, PoolingCount, true>
    {
    public:
        PoolAllocatorImpl();
        ~PoolAllocatorImpl();

    private:
        void* _poolBlocks = nullptr;
        size_t size;
        size_t freeListHead;

    public:
        void*   allocateImpl(KE_IN const size_t count);
        void    deallocateImpl(KE_IN void* ptr, KE_IN const size_t count);
    };

    template <typename T, size_t PoolingCount>
    class PoolAllocatorImpl<T, PoolingCount, false>
    {
    public:
        PoolAllocatorImpl();
        ~PoolAllocatorImpl();

    private:
        void* _poolBlocks = nullptr;
        size_t size;
        size_t freeListHead;

    public:
        void*   allocateImpl(KE_IN const size_t count);
        void    deallocateImpl(KE_IN void* ptr, KE_IN const size_t count);
    };

    template<typename T, size_t PoolingCount>
    class PoolAllocator : public IMemoryAllocator
    {
    public:
        PoolAllocator() = default;
        ~PoolAllocator() = default;

    protected:
        static constexpr bool _isEmbedFreelist = (sizeof(T) > sizeof(size_t));
		PoolAllocatorImpl<T, PoolingCount, _isEmbedFreelist> _poolAllocatorImpl;

    public:
        virtual void*   allocate(KE_IN const size_t count) override;
        virtual void    deallocate(KE_IN void* ptr, KE_IN const size_t count) override;
    };
}