#pragma once
#include "Vector.h"
#include "ContainerTraits.h"

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
		: _allocator(), _memoryEntry(nullptr, 0), _count(0)
	{
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");
	}
	template<typename T, typename Alloc>
	Vector<T, Alloc>::~Vector()
	{
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN const T& element)
	{
		if (_count >= _memoryEntry._capacity)
		{
			reallocateAndMove(KEMemory::CalculateExpandCapacity(_count, _memoryEntry._capacity));
		}

		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		new (firstElem + _count) T(element);
		_count++;
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN T&& element)
	{
		if (_count >= _memoryEntry._capacity)
		{
			reallocateAndMove(KEMemory::CalculateExpandCapacity(_count, _memoryEntry._capacity));
		}

		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		new (firstElem + _count) T(static_cast<T&&>(element));
		_count++;
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::popBack()
	{
		if (_memoryEntry._address == nullptr || _count == 0) return;

		_count--;

		size_t shrinkCapacity = KEMemory::CalculateShrinkCapacity(_count, _memoryEntry._capacity);
		if (shrinkCapacity < _memoryEntry._capacity)
		{
			reallocateAndMove(shrinkCapacity);
		}
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::reallocateAndMove(size_t newCapacity)
	{
		if (newCapacity == _memoryEntry._capacity) return;

		MemoryEntry newMemoryEntry = _allocator.allocate(newCapacity);

		T* oldElements = reinterpret_cast<T*>(_memoryEntry._address);
		T* newElements = reinterpret_cast<T*>(newMemoryEntry._address);

		if constexpr (KETrait::IsTriviallyCopyable<T>::value)
		{
			memcpy(newMemoryEntry._address, _memoryEntry._address, KEMemory::getSizeOfN<T>(_count));
		}
		else
		{
			for (size_t idx = 0; idx < _count; ++idx)
			{
				new (newElements + idx) T(static_cast<T&&>(oldElements[idx]));
			}
		}

		_allocator.deallocate(_memoryEntry);
		_memoryEntry = newMemoryEntry;
		_data = reinterpret_cast<T*>(newMemoryEntry._address);
	}
}