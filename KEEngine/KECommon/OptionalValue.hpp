#pragma once
#include "OptionalValue.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename T>
	inline OptionalValue<T>::OptionalValue() : _hasValue(false) {}

	template<typename T>
	inline OptionalValue<T>::OptionalValue(const T& value)
		: _hasValue(true)
	{
		new (reinterpret_cast<void*>(&_storage)) T(value);
	}

	template<typename T>
	inline OptionalValue<T>::OptionalValue(T&& value)
		: _hasValue(true)
	{
		new (reinterpret_cast<void*>(&_storage)) T(move(value));
	}

	template<typename T>
	inline OptionalValue<T>::OptionalValue(const OptionalValue<T>& value)
		: _hasValue(value._hasValue)
	{
		if (_hasValue)
		{
			new (reinterpret_cast<void*>(&_storage)) T(value.getValue());
		}
	}
	
	template<typename T>
	inline OptionalValue<T>::OptionalValue(OptionalValue<T>&& value)
		: _hasValue(move(value._hasValue))
	{
		if (_hasValue)
		{
			new (reinterpret_cast<void*>(&_storage)) T(move(value.getValue()));
			value._hasValue = false;
		}
	}

	template<typename T>
	inline bool OptionalValue<T>::hasValue() const { return _hasValue; }

	template<typename T>
	inline T* OptionalValue<T>::tryGetValue()
	{
		return _hasValue ? reinterpret_cast<T*>(&_storage) : nullptr;
	}

	template<typename T>
	inline T& OptionalValue<T>::getValue()
	{
		DEBUG_ASSERT(_hasValue, "OptionalValue does not contain a value.");
		return *reinterpret_cast<T*>(&_storage);
	}

	inline OptionalValue<void>::OptionalValue()
		: _hasValue(false)
	{
	}

	inline OptionalValue<void>::OptionalValue(nullptr_t)
		: _hasValue(false)
	{
	}

	inline OptionalValue<void>::OptionalValue(const OptionalValue<void>& value)
		: _hasValue(value._hasValue)
	{
	}

	inline OptionalValue<void>::OptionalValue(OptionalValue<void>&& value)
		: _hasValue(move(value._hasValue))
	{
	}
}
