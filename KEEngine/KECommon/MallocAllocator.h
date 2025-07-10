#pragma once
#include "IMemoryAllocator.h"

namespace ke
{
	template<typename T>
	class MallocAllocator : public IMemoryAllocator
	{
	public:
		virtual MemoryEntry		allocate(KE_IN const size_t count)			override;
		virtual void			deallocate(const MemoryEntry& memoryEntry)	override;
	};
}

