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
	MemoryEntry MallocAllocator<T>::allocate(KE_IN const size_t count)
	{
		return MemoryEntry(KEMemory::aligendMalloc<T>(count), count);
	}

	template<typename T>
	void MallocAllocator<T>::deallocate(KE_IN MemoryEntry& memoryEntry)
	{
		_aligned_free(memoryEntry._address);
		memoryEntry._address = nullptr;
		memoryEntry._capacity = 0;
	}
}