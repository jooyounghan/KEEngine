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
        virtual MemoryEntry     allocate(KE_IN const size_t count)                  override;
        virtual void            deallocate(KE_IN const MemoryEntry& memoryEntry)    override;
    };
}

#include "PoolAllocator.hpp"