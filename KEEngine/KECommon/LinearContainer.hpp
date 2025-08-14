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
				T* elemPtr = _data[idx];
				if (elemPtr == nullptr) continue;

				elemPtr.~T();
			}
		}
		KEMemory::aligendFree<T>(_data);
	}

} 