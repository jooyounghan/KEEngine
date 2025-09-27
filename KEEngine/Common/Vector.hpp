#pragma once
#include "Vector.h"

namespace ke
{
	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> init)
	{
		reserve(init.size());
		for (const T& element : init)
			pushBack(element);
	}

	template<typename T>
	void Vector<T>::pushBack(const T& element)
	{
		pushBackImpl(element);
	}

	template<typename T>
	void Vector<T>::pushBack(T&& element)
	{
		pushBackImpl(element);
	}

	template<typename T>
	void Vector<T>::popBack()
	{
		if (__super::_data == nullptr || __super::_count == 0) return;

		decreaseCount(__super::_count - 1);
		reallocateCapcity(KEMemory::CalculateTargetCapacity(__super::_count, _capacity));
	}

	template<typename T>
	template<typename U>
	void Vector<T>::pushBackImpl(U&& element)
	{
		if (__super::_count >= _capacity)
		{
			reallocateCapcity(KEMemory::CalculateTargetCapacity(__super::_count + 1, _capacity));
		}

		new (__super::_data + __super::_count) T(forward<U>(element));
		__super::_count++;
	}

	template<typename T>
	template<typename... Args>
	void Vector<T>::resize(size_t newSize, Args&&... args)
	{
		if (newSize < __super::_count)
		{
			decreaseCount(newSize);
			reallocateCapcity(KEMemory::CalculateTargetCapacity(newSize, _capacity));
		}
		else
		{
			reallocateCapcity(newSize);
			while (newSize > __super::_count)
			{
				new (__super::_data + __super::_count) T(args...);
				__super::_count++;
			}
		}
	}

	template<typename T>
	void Vector<T>::reserve(size_t newCapacity)
	{
		if (newCapacity > _capacity)
		{
			reallocateCapcity(newCapacity);
		}
	}

	template<typename T>
	void Vector<T>::reallocateCapcity(size_t newCapacity)
	{
		if (newCapacity == _capacity) return;
		_capacity = newCapacity;

		T* newData = reinterpret_cast<T*>(KEMemory::aligendMalloc<false, T>(newCapacity));

		size_t copyCount = __super::_count < newCapacity ? __super::_count : newCapacity;
		if constexpr (KETrait::IsTriviallyCopyable<T>::value)
		{
			memcpy(newData, __super::_data, KEMemory::getPaddedSizeOf<T>() * copyCount);
		}
		else
		{
			for (size_t idx = 0; idx < copyCount; ++idx)
			{
				new (newData + idx) T(move(__super::_data[idx]));
			}
		}

		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			for (size_t idx = 0; idx < __super::_count; ++idx)
			{
				__super::_data[idx].~T();
			}
		}
		
		KEMemory::aligendFree(__super::_data);
		__super::_data = newData;
	}

	template<typename T>
	void Vector<T>::decreaseCount(size_t newCount)
	{
		if (newCount >= __super::_count) return;

		if constexpr (!KETrait::IsTriviallyCopyable<T>::value)
		{
			for (size_t i = newCount; i < __super::_count; ++i)
			{
				__super::_data[i].~T();
			}
		}
		__super::_count = newCount;
	}
}