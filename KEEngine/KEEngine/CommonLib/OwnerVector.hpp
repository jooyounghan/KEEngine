#include "OwnerVector.h"

namespace ke
{
	template<typename T>
	OwnerVector<T>::~OwnerVector()
	{
		reset();
	}

	template<typename T>
	OwnerVector<T>::OwnerVector(OwnerVector&& ownerVector)
	{
		reset();
		move(std::move(ownerVector));
	}

	template<typename T>
	OwnerVector<T>& OwnerVector<T>::operator=(OwnerVector&& ownerVector)
	{
		reset();
		move(std::move(ownerVector));
	}

	template<typename T>
	void OwnerVector<T>::move(OwnerVector&& ownerVector)
	{
		_pointer = ownerVector._pointer;
		ownerVector._pointer = nullptr;
		_count = ownerVector._count;
		ownerVector._count = 0;
	}

	template<typename T>
	size_t OwnerVector<T>::calculateTargetCapacity(const size_t targetCount, const size_t currentCapacity)
	{
		if (targetCount > currentCapacity)
		{
			size_t newCapacity = targetCount + (targetCount >> 1) + (targetCount & 1);
			return (newCapacity > 0) ? newCapacity : 1u;
		}
		else
		{
			size_t shrinkThreshold = static_cast<size_t>(static_cast<float>(currentCapacity) * 0.5f);
			return (targetCount < shrinkThreshold) ? shrinkThreshold : currentCapacity;
		}
	}

	template<typename T>
	void OwnerVector<T>::reallocateCapacity(size_t newCapacity)
	{
		if (newCapacity == _capacity) return;
		_capacity = newCapacity;

		T** newData = new T* [newCapacity];
		memcpy(newData, _pointer, sizeof(T*) * _count);
		clearPointerContainerXXX();
		_pointer = newData;
	}

	template<typename T>
	void OwnerVector<T>::swap(const size_t idx1, const size_t idx2)
	{
		if (idx1 == idx2) return;
		T* element1 = _pointer[idx1];
		_pointer[idx1] = _pointer[idx2];
		_pointer[idx2] = element1;
	}

	template<typename T>
	T* OwnerVector<T>::push_back(T* ptr)
	{
		if (_count >= _capacity)
		{
			reallocateCapacity(calculateTargetCapacity(_count + 1, _capacity));
		}

		_pointer[_count] = ptr;
		_count++;

		return ptr;
	}

	template<typename T>
	template<typename U, typename ...Args>
	T* OwnerVector<T>::push_back(Args ...args)
	{
		if (_count >= _capacity)
		{
			reallocateCapacity(calculateTargetCapacity(_count + 1, _capacity));
		}

		T*& targetPointer = _pointer[_count];
		targetPointer = static_cast<T*>(new U(std::forward<Args>(args)...));
		_count++;

		return targetPointer;
	}

	template<typename T>
	void OwnerVector<T>::pop_back()
	{
		if (_count == 0) return;
		delete _pointer[_count - 1];
		_count--;
		reallocateCapacity(calculateTargetCapacity(_count, _capacity));
	}

	template<typename T>
	template<typename ...Args>
	void OwnerVector<T>::insert(const size_t idx, bool preserveOrder, Args... args)
	{
		T* insertedPointer = push_back(std::forward<Args>(args)...);
		if (preserveOrder && idx < (_count - 1))
		{
			memmove(&_pointer[idx + 1], &_pointer[idx], ((_count - 1) - idx) * sizeof(T*));
			_pointer[idx] = insertedPointer;
		}
		else
		{
			swap(idx, _count - 1);
		}
	}

	template<typename T>
	void OwnerVector<T>::erase(const size_t idx, bool preserveOrder/* = true*/)
	{
		delete _pointer[idx];

		if (idx < _count - 1)
		{
			if (preserveOrder)
			{
				memmove(&_pointer[idx], &_pointer[idx + 1], (_count - 1 - idx) * sizeof(T*));
			}
			else
			{
				_pointer[idx] = _pointer[_count - 1];
			}
		}

		_pointer[_count - 1] = nullptr;
		_count--;
	}

	template<typename T>
	void OwnerVector<T>::reset()
	{
		for (size_t idx = 0; idx < _count; ++idx)
		{
			delete _pointer[idx];
		}
		clearPointerContainerXXX();
	}
}