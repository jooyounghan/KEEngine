#pragma once
#include "Vector.h"

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
		: _allocator(), _memoryEntry(nullptr, 0), _count(0)
	{

	}
	template<typename T, typename Alloc>
	Vector<T, Alloc>::~Vector()
	{
		reallocateCapcity(0);
	}

	template<typename T, typename Alloc>
	inline size_t Vector<T, Alloc>::size() const { return _count; }

	template<typename T, typename Alloc>
	inline size_t Vector<T, Alloc>::capacity() const { return _memoryEntry._capacity; }

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN const T& element)
	{
		pushBackImpl(element);
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN T&& element)
	{
		pushBackImpl(element);
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::popBack()
	{
		if (_memoryEntry._address == nullptr || _count == 0) return;

		decreaseCount(_count - 1);
		reallocateCapcity(KEMemory::CalculateTargetCapacity(_count, _memoryEntry._capacity));
	}

	template<typename T, typename Alloc>
	template<typename U>
	void Vector<T, Alloc>::pushBackImpl(KE_IN U&& element)
	{
		if (_count >= _memoryEntry._capacity)
		{
			reallocateCapcity(KEMemory::CalculateTargetCapacity(_count + 1, _memoryEntry._capacity));
		}

		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		new (firstElem + _count) T(forward<U>(element));
		_count++;
	}

	template<typename T, typename Alloc>
	template<typename... Args>
	void Vector<T, Alloc>::resize(size_t newSize, Args&&... args)
	{
		if (newSize < _count)
		{
			decreaseCount(newSize);
			reallocateCapcity(KEMemory::CalculateTargetCapacity(newSize, _memoryEntry._capacity));
		}
		else
		{
			reallocateCapcity(newSize);
			T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
			while (newSize > _count)
			{
				new (firstElem + _count) T(args...);
				_count++;
			}
		}
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::reserve(size_t newCapacity)
	{
		if (newCapacity > _memoryEntry._capacity)
		{
			reallocateCapcity(newCapacity);
		}
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::reallocateCapcity(size_t newCapacity)
	{
		if (newCapacity == _memoryEntry._capacity) return;

		MemoryEntry newMemoryEntry = _allocator.allocate<false>(newCapacity);
		T* oldElements = reinterpret_cast<T*>(_memoryEntry._address);
		T* newElements = reinterpret_cast<T*>(newMemoryEntry._address);

		size_t copyCount = _count < newCapacity ? _count : newCapacity;

		if constexpr (KETrait::IsTriviallyCopyable<T>::value)
		{
			memcpy(newMemoryEntry._address, _memoryEntry._address, KEMemory::getPaddedSizeOf<T>() * copyCount);
		}
		else
		{
			for (size_t idx = 0; idx < copyCount; ++idx)
			{
				new (newElements + idx) T(static_cast<T&&>(oldElements[idx]));
			}
		}

		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			for (size_t idx = 0; idx < _count; ++idx)
			{
				oldElements[idx].~T();
			}
		}

		_allocator.deallocate(_memoryEntry);
		_memoryEntry = newMemoryEntry;

#ifdef _DEBUG
		_data = reinterpret_cast<T*>(newMemoryEntry._address);
#endif
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::decreaseCount(size_t newCount)
	{
		if (newCount >= _count) return;

		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
			for (size_t i = newCount; i < _count; ++i)
			{
				firstElem[i].~T();
			}
		}
		_count = newCount;
	}
}