#pragma once
#include "TypeCommon.h"

namespace ke
{
	class IMemoryAllocator
	{
	public:
		virtual ~IMemoryAllocator() = default;
		virtual void* allocate() = 0;
		virtual void deallocate(KE_IN void* ptr) = 0;
	};
}
