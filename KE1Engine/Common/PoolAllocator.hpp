#pragma once
#include "PoolAllocator.h"
#include "MemoryCommon.h"

namespace ke
{
    static uintptr_t getBlockAddress(void* ptr)
    {
        return reinterpret_cast<uintptr_t>(ptr);
    }

    static uintptr_t getNextBlockAddress(void* ptr)
    {
        return *reinterpret_cast<uintptr_t*>(ptr);
    }

    static void writeBlockAddress(void* ptr, uintptr_t value)
	{
		if (ptr == nullptr)
		{
			return;
		}
		*reinterpret_cast<uintptr_t*>(ptr) = value;
	}

    template<typename T, size_t PoolingCount>
    PoolAllocator<T, PoolingCount>::PoolAllocator()
    {
        static_assert(KETrait::AllocatorTrait<PoolAllocator<T, PoolingCount>>::value, "Allocator does not satisfy the required AllocatorTrait");

        static_assert(sizeof(T) >= sizeof(size_t), "T must be at least the size of a pointer.");
        static_assert(PoolingCount > 0, "PoolingCount must be positive.");

        _poolBlocks = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(PoolingCount));

        for (size_t idx = 0; idx < PoolingCount - 1; ++idx)
        {
            writeBlockAddress(_poolBlocks + idx, getBlockAddress(_poolBlocks + (idx + 1)));
        }
        writeBlockAddress(_poolBlocks + PoolingCount - 1, getBlockAddress(nullptr));
        _freeListHead = _poolBlocks;
    }

    template<typename T, size_t PoolingCount>
    PoolAllocator<T, PoolingCount>::~PoolAllocator()
    {
		if (_poolBlocks != nullptr)
		{
			KEMemory::aligendFree(_poolBlocks);
			_poolBlocks = nullptr;
		}
		_freeListHead = nullptr;
    }

    template<typename T, size_t PoolingCount>
    template<bool InitializeNull>
    MemoryEntry PoolAllocator<T, PoolingCount>::allocate(const size_t count)
    {
        if (count == 0 || count > PoolingCount) return MemoryEntry(nullptr, 0);

        T* result = _freeListHead;
		T* current = _freeListHead;
        for (size_t idx = 0; idx < count; ++idx)
        {
			if (current == nullptr) return MemoryEntry(nullptr, 0);

            uintptr_t nextBlock = getNextBlockAddress(current);
            current = getBlockAddress(current + 1) == nextBlock ? reinterpret_cast<T*>(nextBlock) : nullptr;
        }

		_freeListHead = current;

        if constexpr (InitializeNull)
        {
            memset(result, 0, count * KEMemory::getSizeOf<T>());
		}

        return MemoryEntry(result, count);
    }

    template<typename T, size_t PoolingCount>
    void PoolAllocator<T, PoolingCount>::deallocate(MemoryEntry& memoryEntry)
    {
		void* ptr = memoryEntry._address;
		size_t count = memoryEntry._capacity;

        if (ptr == nullptr || count == 0) return;

		T* block = reinterpret_cast<T*>(ptr);
        for (size_t idx = 0; idx < count - 1; ++idx)
        {
			writeBlockAddress(block + idx, getBlockAddress(block + (idx + 1)));
        }

		writeBlockAddress(block + (count - 1), getBlockAddress(_freeListHead));
        _freeListHead = block;

		memoryEntry._address = nullptr;
		memoryEntry._capacity = 0;
    }
}


