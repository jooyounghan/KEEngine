#pragma once
#include "TypeTraits.h"
#include "IMemoryAllocator.h"

namespace ke
{
	template<typename T, typename Alloc>
	class IConatiner
	{
	public:
		IConatiner() { static_assert(KETrait::IsBaseOf<IMemoryAllocator, Alloc>::value, "The template parameter Alloc is required to derive from IMemoryAllocator."); }
		
	public:
		virtual ~IConatiner() = default;
		virtual void pushBack(KE_IN const T& element) = 0;
		virtual void pushBack(KE_IN T&& element) = 0;
		virtual void popBack(KE_OUT T* elementOut) = 0;
	};
}