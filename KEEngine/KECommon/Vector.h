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
		NO_UNIQUE_ADDRESS Alloc		_allocator;
		MemoryEntry					_memoryEntry;
		size_t						_count;
		size_t						_shrinkThreshold;

	private:
		const T*		_data;

	public:
		inline size_t size() const { return _count; }
		inline size_t capacity() const { return _memoryEntry._capacity; }

	public:
		void pushBack(KE_IN const T& element);
		void pushBack(KE_IN T&& element);
		void popBack();


	private:
		void reallocateAndMove(size_t newCapacity);
	};
}

#include "Vector.hpp"
