#pragma once
#include "IMemoryAllocator.h"

namespace ke
{
    template<typename T, size_t PoolingCount>
    class PoolAllocator : public IMemoryAllocator
    {
    public:
        PoolAllocator();
        ~PoolAllocator();

    private:
        T*  _poolBlocks;
        T*  _freeListHead;

    public:
        virtual void*   allocate() override;
        virtual void    deallocate(KE_IN void* ptr) override;
    };
}