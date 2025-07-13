#pragma once
#include "MallocAllocator.h"
#include "iterator.h"

namespace ke
{
	template<typename T, typename Alloc = MallocAllocator<T>>
	class Vector
	{
	public:
		Vector();
		~Vector();

	private:
		Alloc			_allocator;
		MemoryEntry		_memoryEntry;
		size_t			_size;

	public:
		void pushBack(KE_IN const T& element);
		void pushBack(KE_IN T&& element);
		void popBack(KE_OUT T* elementOut);
	};
}

#include "Vector.hpp"
