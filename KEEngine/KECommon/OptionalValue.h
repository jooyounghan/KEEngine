#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<typename T>
	class OptionalValue
	{
	public:
		OptionalValue();
		OptionalValue(const T& value);
		OptionalValue(T&& value);
		OptionalValue(const OptionalValue<T>& value);
		OptionalValue(OptionalValue<T>&& value);

	public:
		bool hasValue() const;
		T* tryGetValue();

	private:
		T& getValue();

	private:
		bool _hasValue = false;
		alignas(T) uint8 _storage[sizeof(T)];

#ifdef _DEBUG
	private:
		const T* _valuePtr = reinterpret_cast<T*>(&_storage);
#endif
	};

	template<>
	class OptionalValue<void>
	{
	public:
		OptionalValue();
		OptionalValue(nullptr_t);
		OptionalValue(const OptionalValue<void>& value);
		OptionalValue(OptionalValue<void>&& value);

	private:
		bool _hasValue = false;
	};
}

#include "OptionalValue.hpp"