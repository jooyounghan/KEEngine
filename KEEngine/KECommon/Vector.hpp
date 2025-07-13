#pragma once
#include "Vector.h"
#include "ContainerTraits.h"

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
		: _allocator(), _memoryEntry(nullptr, 0), _size(0)
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
		if (_memoryEntry._address == nullptr || _size >= _memoryEntry._count)
		{
			size_t newCapacity = KEMemory::CalculateNewSize(_memoryEntry._count, _size + 1);
			MemoryEntry newMemoryEntry = _allocator.allocate(newCapacity);

			T* oldElements = reinterpret_cast<T*>(_memoryEntry._address);
			T* newElements = reinterpret_cast<T*>(newMemoryEntry._address);

			if constexpr (KETrait::IsTriviallyCopyable<T>::value)
			{
				memcpy(newMemoryEntry._address, _memoryEntry._address, KEMemory::getSizeOfN<T>(_size));
			}
			else
			{
				for (size_t idx = 0; idx < _size; ++idx)
				{
					new (newElements + idx) T(oldElements[idx]);
				}
			}

			_allocator.deallocate(_memoryEntry);
			_memoryEntry = newMemoryEntry;			
		}

		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		T& targetElement = firstElem[_size];
		targetElement = element;
		_size++;
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN T&& element)
	{
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::popBack(KE_OUT T* elementOut)
	{
	}
}