#pragma once
#include "MallocAllocator.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename T>
	MallocAllocator<T>::MallocAllocator()
	{
		static_assert(KETrait::AllocatorTrait<MallocAllocator<T>>::value, "Allocator does not satisfy the required AllocatorTrait.");
	}

	template<typename T>
	template<bool InitializeNull>
	MemoryEntry MallocAllocator<T>::allocate(const size_t count)
	{
		return MemoryEntry(KEMemory::aligendMalloc<InitializeNull, T>(count), count);
	}

	template<typename T>
	void MallocAllocator<T>::deallocate(MemoryEntry& memoryEntry)
	{
		if (memoryEntry._address != nullptr)
		{
			_aligned_free(memoryEntry._address);
			memoryEntry._address = nullptr;
			memoryEntry._capacity = 0;
		}
	}
}