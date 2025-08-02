#pragma once
#include "MallocAllocator.h"
#include "iterator.h"

#include "ContainerTraits.h"

namespace ke
{
	template<typename T, typename Alloc = MallocAllocator<T>>
	class Vector
	{
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");

	public:
		Vector();
		~Vector();

	private:
		NO_UNIQUE_ADDRESS Alloc		_allocator;
		MemoryEntry					_memoryEntry;
		size_t						_count;
		size_t						_shrinkThreshold;

#ifdef _DEBUG
	private:
		const T*		_data;
#endif

	public:
		inline size_t size() const;
		inline size_t capacity() const;

	public:
		void pushBack(KE_IN const T& element);
		void pushBack(KE_IN T&& element);

	private:
		template<typename U>
		void pushBackImpl(KE_IN U&& element);

	public:
		void popBack();

	public:
		template<typename... Args>
		void resize(size_t newSize, Args&&... args);
		void reserve(size_t newCapacity);

	private:
		void reallocateCapcity(size_t newCapacity);
		void decreaseCount(size_t newCount);
	};
}

#include "Vector.hpp"
