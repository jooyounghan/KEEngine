#pragma once
#include "TypeCommon.h"

namespace ke
{
	class IMemoryAllocator
	{
	public:
		virtual ~IMemoryAllocator()											= default;
		virtual void* allocate(KE_IN const size_t count)					= 0;
		virtual void deallocate(KE_IN void* ptr, KE_IN const size_t count)	= 0;
	};
}
