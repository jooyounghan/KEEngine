#pragma once
#include "Iterator.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename T>
	inline Iterator<T>::Iterator(T& target)
		: _targetAddress(KEMemory::AddressOf(target))
	{
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator++()
	{
		++_targetAddress;
		return *this;
	}
	template<typename T>
	inline T& Iterator<T>::operator*()
	{
		DEBUG_ASSERT(_targetAddress != nullptr, "Iterator is targeting nullptr");
		return *_targetAddress;
	}
	template<typename T>
	inline bool Iterator<T>::operator!=(const Iterator& other) const
	{
		return _targetAddress != other._targetAddress;
	}

	template<typename T>
	inline ConstIterator<T>::ConstIterator(T& target)
		: _targetAddress(KEMemory::AddressOf(target))
	{
	}
	template<typename T>
	inline ConstIterator<T> ConstIterator<T>::operator++()
	{
		++_targetAddress;
		return *this;
	}
	template<typename T>
	inline const T& ConstIterator<T>::operator*()
	{
		DEBUG_ASSERT(_targetAddress != nullptr, "ConstIterator is targeting nullptr");
		return *_targetAddress;
	}
	template<typename T>
	inline bool ConstIterator<T>::operator!=(const ConstIterator& other) const
	{
		return _targetAddress != other._targetAddress;
	}
}