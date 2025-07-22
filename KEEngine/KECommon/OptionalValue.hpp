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
		new (GET_BUFFER_PTR_AT(T, _storage, 0)) T(value);
	}

	template<typename T>
	inline OptionalValue<T>::OptionalValue(T&& value)
		: _hasValue(true)
	{
		new (GET_BUFFER_PTR_AT(T, _storage, 0)) T(move(value));
	}

	template<typename T>
	inline OptionalValue<T>::OptionalValue(const OptionalValue<T>& value)
		: _hasValue(value._hasValue)
	{
		if (_hasValue)
		{
			new (GET_BUFFER_PTR_AT(T, _storage, 0)) T(value.getValue());
		}
	}
	
	template<typename T>
	inline OptionalValue<T>::OptionalValue(OptionalValue<T>&& value)
		: _hasValue(move(value._hasValue))
	{
		if (_hasValue)
		{
			new (GET_BUFFER_PTR_AT(T, _storage, 0)) T(move(value.getValue()));
			value._hasValue = false;
		}
	}

	template<typename T>
	inline bool OptionalValue<T>::hasValue() const { return _hasValue; }

	template<typename T>
	inline T* OptionalValue<T>::tryGetValue()
	{
		return _hasValue ? GET_BUFFER_PTR_AT(T, _storage, 0) : nullptr;
	}

	template<typename T>
	inline T& OptionalValue<T>::getValue()
	{
		DEBUG_ASSERT(_hasValue, "OptionalValue does not contain a value.");
		return *GET_BUFFER_PTR_AT(T, _storage, 0);
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
