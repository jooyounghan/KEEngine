#pragma once
#include "IContainer.h"
#include "MallocAllocator.h"

namespace ke
{
	template<typename T, typename Alloc = MallocAllocator<T>>
	class Vector : public IConatiner<T, Alloc>
	{
	public:
		Vector();
		virtual ~Vector() override;

	public:
		virtual void pushBack(KE_IN const T& element) override;
		virtual void pushBack(KE_IN T&& element) override;
		virtual void popBack(KE_OUT T* elementOut) override;
	};
}

#include "Vector.hpp"
