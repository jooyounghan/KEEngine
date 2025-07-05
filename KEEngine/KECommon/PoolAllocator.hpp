#include "PoolAllocator.h"
#include "MemoryCommon.h"

namespace ke
{
    inline constexpr uintptr_t nullptrValue = reinterpret_cast<uintptr_t>((void*)nullptr);

    inline static uintptr_t getBlockAddress(void* ptr)
    {
        return reinterpret_cast<uintptr_t>(ptr);
    }

    inline static uintptr_t getNextBlockAddress(void* ptr)
    {
        return *reinterpret_cast<uintptr_t*>(ptr);
    }

    inline static void writeBlockAddress(void* ptr, uintptr_t value)
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
        static_assert(sizeof(T) >= sizeof(size_t), "T must be at least the size of a pointer.");
        static_assert(PoolingCount > 0, "PoolingCount must be positive.");

        _poolBlocks = reinterpret_cast<T*>(KEMemory::aligendMalloc<T>(PoolingCount));

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
        free(_poolBlocks);
        _poolBlocks = nullptr;
    }

    template<typename T, size_t PoolingCount>
    void* PoolAllocator<T, PoolingCount>::allocate()
    {
        void* pooledObject = nullptr;
        if (_freeListHead != nullptr)
        {
            pooledObject = _freeListHead;
            uintptr_t nextBlockAddress = getNextBlockAddress(_freeListHead);
            _freeListHead = reinterpret_cast<T*>(nextBlockAddress == nullptrValue ? nullptrValue : nextBlockAddress);
        }

		return pooledObject;
    }

    template<typename T, size_t PoolingCount>
    void PoolAllocator<T, PoolingCount>::deallocate(KE_IN void* ptr)
    {
        T* prevFreeListHead = _freeListHead;
        _freeListHead = reinterpret_cast<T*>(ptr);
        writeBlockAddress(_freeListHead, getBlockAddress(prevFreeListHead));
    }
}


