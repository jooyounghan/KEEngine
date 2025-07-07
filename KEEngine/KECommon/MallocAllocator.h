#pragma once
#include "IMemoryAllocator.h"

namespace ke
{
	template<typename T>
	class MallocAllocator : public IMemoryAllocator
	{
	public:
		virtual void*	allocate(KE_IN const size_t count)						override;
		virtual void	deallocate(KE_IN void* ptr, KE_IN const size_t count)	override;
	};
}

