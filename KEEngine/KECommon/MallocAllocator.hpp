#pragma once
#include "MallocAllocator.h"
#include "MemoryCommon.h"

namespace ke
{	
	template<typename T>
	MemoryEntry MallocAllocator<T>::allocate(KE_IN const size_t count)
	{
		return MemoryEntry(KEMemory::aligendMalloc<T>(count), count);
	}

	template<typename T>
	void MallocAllocator<T>::deallocate(KE_IN const MemoryEntry& memoryEntry)
	{
		return delete(memoryEntry._address, KEMemory::getSizeOfN<T>(memoryEntry._count));
	}
}