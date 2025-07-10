#pragma once
#include "TypeCommon.h"

namespace ke
{
	struct MemoryEntry
	{
		explicit MemoryEntry(void* address = nullptr, size_t count = 0)
			: _address(address), _count(count) 
		{
		}
		void*	_address;
		size_t	_count;
	};

	class IMemoryAllocator
	{
	public:
		virtual ~IMemoryAllocator()										= default;
		virtual MemoryEntry allocate(KE_IN const size_t count)			= 0;
		virtual void deallocate(KE_IN const MemoryEntry& memoryEntry)			= 0;
	};
}
