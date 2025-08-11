#pragma once
#include "StaticArray.h"

namespace ke
{
	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>::StaticArray()
	{
		InitializeStorage();
	}

	template<size_t Count, typename T, typename Alloc>
	template<typename ...Args>
	StaticArray<Count, T, Alloc>::StaticArray(Args ...args)
	{
		InitializeStorage();
		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (firstElem + idx) T(args...);
		}
	}

	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>::StaticArray(const StaticArray& other)
	{
		InitializeStorage();
		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		const T* otherFirstElem = reinterpret_cast<const T*>(other._memoryEntry._address);
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (firstElem + idx) T(otherFirstElem[idx]);
		}
	}

	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>::StaticArray(StaticArray&& other) noexcept
	{
		_memoryEntry = other._memoryEntry;
		other._memoryEntry._address = nullptr;
		other._memoryEntry._capacity = 0;
	}

	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>::~StaticArray()
	{
		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			T* _firstElem = reinterpret_cast<T*>(_memoryEntry._address);
			for(size_t idx = 0; idx < Count; ++idx)
			{

				T* elemPtr = _firstElem + idx;
				if (elemPtr == nullptr) continue;

				elemPtr.~T();
			}
		}

		_allocator.deallocate(_memoryEntry);
	}

	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>& StaticArray<Count, T, Alloc>::operator=(const StaticArray& other)
	{
		if (this == &other) return *this;

		_allocator.deallocate(_memoryEntry);
		InitializeStorage();
		T* firstElem = reinterpret_cast<T*>(_memoryEntry._address);
		const T* otherFirstElem = reinterpret_cast<const T*>(other._memoryEntry._address);
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (firstElem + idx) T(otherFirstElem[idx]);
		}
		return *this;
	}

	template<size_t Count, typename T, typename Alloc>
	StaticArray<Count, T, Alloc>& StaticArray<Count, T, Alloc>::operator=(StaticArray&& other) noexcept
	{
	}

	template<size_t Count, typename T, typename Alloc>
	inline void StaticArray<Count, T, Alloc>::InitializeStorage() noexcept
	{
		_memoryEntry = _allocator.allocate<true>(Count);

#ifdef _DEBUG
		_data = reinterpret_cast<const T*>(_memoryEntry._address);
#endif
	}
}