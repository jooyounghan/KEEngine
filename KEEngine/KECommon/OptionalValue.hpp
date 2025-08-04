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
	OptionalValue<Types...>::~OptionalValue()
	{
		if (_hasValue)
		{
			_hasValue = false;
			destruct<0>();
		}
	}

	template<typename ...Types>
	OptionalValue<Types...>& OptionalValue<Types...>::operator=(const OptionalValue& other)

	{
		if (this != &other)
		{
			this->~OptionalValue<Types...>();
			_hasValue = other._hasValue;
			if (_hasValue) 
			{
				copyFrom<0>(other);
			}
		}
		return *this;
	}

	template<typename ...Types>
	OptionalValue<Types...>& OptionalValue<Types...>::operator=(OptionalValue&& other)

	{
		if (this != &other)
		{
			this->~OptionalValue<Types...>();
			_hasValue = other._hasValue;
			if (_hasValue) 
			{
				moveFrom<0>(move(other));
				other._hasValue = false;
			}
		}
		return *this;
	}

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(const Types & ...value)
	{
		construct<0>(value...);
		_hasValue = true;
	}

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(Types && ...value)
	{
		construct<0>(move(value)...);
		_hasValue = true;
	}

	template<typename ...Types>
	bool OptionalValue<Types...>::hasValue() const { return _hasValue; }

	template<typename ...Types>
	template<size_t Index>
	auto* OptionalValue<Types...>::tryGetValue()
	{
		static_assert(Index < sizeof...(Types), "Index out of bounds for OptionalValue types");
		if (!_hasValue) return static_cast<typename GetType<Index, Types...>::type*>(nullptr);

		using T = typename GetType<Index, Types...>::type;
		constexpr size_t offset = GetOffset<Index, Types...>::value;
		return reinterpret_cast<T*>(_storage + offset);
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::setValue(const GetType<Index, Types...>::type& value)
	{
		using T = typename GetType<Index, Types...>::type;
		construct<Index>(value);
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::setValue(GetType<Index, Types...>::type&& value)
	{
		construct<Index>(move(value));
	}

	template<typename ...Types>
	template<size_t Index, typename T>
	void OptionalValue<Types...>::construct(T&& value)
	{
		using Type = typename GetType<Index, Types...>::type;
		constexpr size_t offset = GetOffset<Index, Types...>::value;
		new (_storage + offset) Type(forward<T>(value));
	}

	template<typename ...Types>
	template<size_t Index, typename T, typename... Ts>
	void OptionalValue<Types...>::construct(T&& first, Ts&&... rest)
	{
		construct<Index>(forward<T>(first));
		construct<Index + 1>(forward<Ts>(rest)...);
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::destruct()
	{
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
