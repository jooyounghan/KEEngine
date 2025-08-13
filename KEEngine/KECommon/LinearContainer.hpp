#pragma once
#include "LinearContainer.h"
#include "MemoryCommon.h"

namespace ke
{
	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>::LinearContainer()
	{
		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<true, T>(InitialCount));
	}

	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>::LinearContainer(const LinearContainer& other) { *this = other; }

	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>::LinearContainer(LinearContainer&& other) noexcept { *this = move(other); }

	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>::~LinearContainer()
	{
		if constexpr (!KETrait::IsTriviallyCopyable<InitialCount, T>::value)
		{
			for (size_t idx = 0; idx < _count; ++idx)
			{
				T* elemPtr = _data[idx];
				if (elemPtr == nullptr) continue;

				elemPtr.~T();
			}
		}
		KEMemory::aligendFree(_data);
	}

	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>& LinearContainer<InitialCount, T>::operator=(const LinearContainer& other)
	{
		if (this == &other) return *this;
		this->~LinearContainer();

		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(other._count));
		for (size_t idx = 0; idx < other._count; ++idx)
		{
			new (&_data[idx]) T(other._data[idx]);
		}
		return *this;
	}

	template<size_t InitialCount, typename T>
	LinearContainer<InitialCount, T>& LinearContainer<InitialCount, T>::operator=(LinearContainer&& other) noexcept
	{
		if (this == &other) return *this;
		this->~LinearContainer();

		this->_data = other._data;
		other._data = nullptr;
		return *this;
	}
} 