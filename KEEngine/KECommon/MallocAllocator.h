#pragma once
#include "TypeCommon.h"
#include "AllocatorTraits.h"

namespace ke
{
	template<typename T>
	class MallocAllocator
	{
	public:
		MallocAllocator();

	public:
		MemoryEntry		allocate(KE_IN const size_t count);
		void			deallocate(KE_IN MemoryEntry& memoryEntry);
	};
}

#include "MallocAllocator.hpp"