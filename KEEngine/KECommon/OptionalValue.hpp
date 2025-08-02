#pragma once
#include "OptionalValue.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(const Types & ...value) { setValue(value...); }

	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(Types && ...value) { setValue(move<Types>(value)...); }

	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(const OptionalValue& other)
		: _hasValue(other._hasValue)
	{
		if (_hasValue)
			copyFrom<0>(other);
	}

	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(OptionalValue&& other)
		: _hasValue(other._hasValue)
	{
		if (_hasValue)
		{
			other._hasValue = false;
			moveFrom<0>(move(other));
		}
	}

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(const Types & ...value)
	{
		construct<0, const Types&...>(value...);
		_hasValue = true;
	}

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(Types && ...value)
	{
		construct<0, Types&&...>(move(value)...);
		_hasValue = true;
	}

	template<typename ...Types>
	bool OptionalValue<Types...>::hasValue() const { return _hasValue; }

	template<typename ...Types>
	template<size_t Index>
	auto* OptionalValue<Types...>::tryGetValue()
	{
		if (!_hasValue) return static_cast<typename GetType<Index, Types...>::type*>(nullptr);

		using T = typename GetType<Index, Types...>::type;
		constexpr size_t offset = GetOffset<Index, Types...>::value;
		return reinterpret_cast<T*>(_storage + offset);
	}
	
	template<typename ...Types>
	template<size_t Index, typename T, typename ...Ts>
	void OptionalValue<Types...>::construct(T&& first, Ts && ...rest)
	{
		using Type = typename GetType<Index, Types...>::type;
		constexpr size_t offset = GetOffset<Index, Types...>::value;
		new (_storage + offset) Type(forward<Type>(first));

		if constexpr (sizeof...(Ts) > 0)
			construct<Index + 1, Ts...>(forward<Ts>(rest)...);
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::copyFrom(const OptionalValue& other)
	{
		if constexpr (Index < sizeof...(Types))
		{
			using Type = typename GetType<Index, Types...>::type;
			constexpr size_t offset = GetOffset<Index, Types...>::value;
			const Type* src = reinterpret_cast<const Type*>(other._storage + offset);
			new (_storage + offset) Type(*src);
			copyFrom<Index + 1>(other);
		}
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::moveFrom(OptionalValue&& other)
	{
		if constexpr (Index < sizeof...(Types))
		{
			using T = typename GetType<Index, Types...>::type;
			constexpr size_t offset = GetOffset<Index, Types...>::value;
			T* src = reinterpret_cast<T*>(other._storage + offset);
			new (_storage + offset) T(move(*src));
			moveFrom<Index + 1>(move(other));
		}
	}
}
