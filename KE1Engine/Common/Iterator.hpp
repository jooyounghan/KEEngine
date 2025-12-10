#pragma once
#include "Iterator.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename T>
	Iterator<T>::Iterator(T& target)
		: _targetAddress(KEMemory::AddressOf(target))
	{
	}

	template<typename T>
	Iterator<T> Iterator<T>::operator++()
	{
		++_targetAddress;
		return *this;
	}
	template<typename T>
	T& Iterator<T>::operator*()
	{
		DEBUG_ASSERT(_targetAddress != nullptr, "Iterator is targeting nullptr");
		return *_targetAddress;
	}
	template<typename T>
	bool Iterator<T>::operator!=(const Iterator& other) const
	{
		return _targetAddress != other._targetAddress;
	}

	template<typename T>
	ConstIterator<T>::ConstIterator(T& target)
		: _targetAddress(KEMemory::AddressOf(target))
	{
	}
	template<typename T>
	ConstIterator<T> ConstIterator<T>::operator++()
	{
		++_targetAddress;
		return *this;
	}
	template<typename T>
	const T& ConstIterator<T>::operator*()
	{
		DEBUG_ASSERT(_targetAddress != nullptr, "ConstIterator is targeting nullptr");
		return *_targetAddress;
	}
	template<typename T>
	bool ConstIterator<T>::operator!=(const ConstIterator& other) const
	{
		return _targetAddress != other._targetAddress;
	}
}