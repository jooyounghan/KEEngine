#pragma once
#include "StaticArray.h"

namespace ke
{
	template<size_t Count, typename T>
	StaticArray<Count, T>::StaticArray()
	{
		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<true, T>(Count));
	}

	template<size_t Count, typename T>
	template<typename ...Args>
	StaticArray<Count, T>::StaticArray(Args ...args)
	{
		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(Count));
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (&_data[idx]) T(args...);
		}
	}

	template<size_t Count, typename T>
	StaticArray<Count, T>::StaticArray(const StaticArray& other) { *this = other; }

	template<size_t Count, typename T>
	StaticArray<Count, T>::StaticArray(StaticArray&& other) noexcept { *this = move(other); }

	template<size_t Count, typename T>
	StaticArray<Count, T>::~StaticArray()
	{
		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			for(size_t idx = 0; idx < Count; ++idx)
			{
				T* elemPtr = _data[idx];
				if (elemPtr == nullptr) continue;

				elemPtr.~T();
			}
		}
		KEMemory::aligendFree(_data);
	}

	template<size_t Count, typename T>
	StaticArray<Count, T>& StaticArray<Count, T>::operator=(const StaticArray& other)
	{
		if (this == &other) return *this;
		this->~StaticArray();

		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(Count));
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (&_data[idx]) T(other._data[idx]);
		}
		return *this;
	}

	template<size_t Count, typename T>
	StaticArray<Count, T>& StaticArray<Count, T>::operator=(StaticArray&& other) noexcept
	{
		if (this == &other) return *this;
		this->~StaticArray();

		this->_data = other._data;
		other._data = nullptr;
		return *this;
	}
}