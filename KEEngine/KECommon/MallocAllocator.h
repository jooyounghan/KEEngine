#pragma once
#include "IMemoryAllocator.h"

namespace ke
{
	template<typename T>
	class MallocAllocator : public IMemoryAllocator
	{
	public:
		virtual void*	allocate() override;
		virtual void	deallocate(KE_IN void* ptr) override;
	};
}

