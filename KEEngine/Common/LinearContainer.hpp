#pragma once
#include "LinearContainer.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>::LinearContainer()
	{
		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<true, T>(InitialCount));
	}

	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>::LinearContainer(const LinearContainer& other) { *this = other; }

	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>::LinearContainer(LinearContainer&& other) noexcept { *this = move(other); }

	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>::~LinearContainer() { release(); }

	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>& LinearContainer<T, InitialCount>::operator=(const LinearContainer& other)
	{
		if (this == &other) return *this;
		release();

		_count = other._count;
		_data = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(other._count));
		for (size_t idx = 0; idx < other._count; ++idx)
		{
			new (_data + idx) T(other._data[idx]);
		}
		return *this;
	}

	template<typename T, size_t InitialCount>
	LinearContainer<T, InitialCount>& LinearContainer<T, InitialCount>::operator=(LinearContainer&& other) noexcept
	{
		if (this == &other) return *this;
		release();

		this->_count = other._count;
		this->_data = other._data;
		other._data = nullptr;
		return *this;
	}

	template<typename T, size_t InitialCount>
	void LinearContainer<T, InitialCount>::release()
	{
		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			for (size_t idx = 0; idx < _count; ++idx)
			{
				T& elemPtr = _data[idx];
				elemPtr.~T();
			}
		}
		KEMemory::aligendFree<T>(_data);
	}

	template<typename T, size_t InitialCount>
	void LinearContainer<T, InitialCount>::swap(size_t idx1, size_t idx2)
	{
		if (idx1 != idx2)
		{
			T temp = move(_data[idx1]);
			_data[idx1] = move(_data[idx2]);
			_data[idx2] = move(temp);
		}
	}

	template<typename T, size_t InitialCount>
	void LinearContainer<T, InitialCount>::swap(size_t idx, T& target)
	{
		T temp = move(_data[idx]);
		_data[idx] = target;
		target = move(temp);
	}
} 