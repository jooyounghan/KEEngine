#pragma once
#include "TypeCommon.h"
#include "AllocatorTraits.h"

namespace ke
{
    template<typename T, size_t PoolingCount>
    class PoolAllocator
    {
    public:
        PoolAllocator();
        ~PoolAllocator();

    private:
        T*  _poolBlocks;
        T*  _freeListHead;

    public:
        template<bool InitializeNull>
        MemoryEntry     allocate(KE_IN const size_t count);
        void            deallocate(KE_IN MemoryEntry& memoryEntry);
    };
}

#include "PoolAllocator.hpp"