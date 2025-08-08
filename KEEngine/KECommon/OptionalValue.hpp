#pragma once
#include "OptionalValue.h"

namespace ke
{
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue() : _hasValue(false) { InitializeStorage(); }
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(const Types & ...value) : _hasValue(false) { InitializeStorage(); setValue(value...); }
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(Types && ...value)  : _hasValue(false) { InitializeStorage(); setValue(move(value)...); }
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(const OptionalValue& other) { InitializeStorage(); *this = other; }
	template<typename ...Types>
	OptionalValue<Types...>::OptionalValue(OptionalValue&& other) { *this = move(other); }

	template<typename ...Types>
	OptionalValue<Types...>::~OptionalValue() { dispose(); }

	template<typename ...Types>
	OptionalValue<Types...>& OptionalValue<Types...>::operator=(const OptionalValue& other)
	{
		if (this != &other)
		{
			this->release();

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
			moveFrom(move(other));
		}
		return *this;
	}

	template<typename ...Types>
	bool OptionalValue<Types...>::hasValue() const { return _hasValue; }

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(const Types & ...value)
	{
		release();
		_hasValue = true;		
		construct<0>(value...);
	}

	template<typename ...Types>
	void OptionalValue<Types...>::setValue(Types && ...value)
	{
		release();
		_hasValue = true;
		construct<0>(move(value)...);
	}


	template<typename ...Types>
	template<size_t Index>
	auto* OptionalValue<Types...>::tryGetValue()
	{
		static_assert(Index < sizeof...(Types), "Index out of bounds for OptionalValue types");
		if (!_hasValue) return static_cast<typename GetType<Index, Types...>::Type*>(nullptr);
		
		using CurrentType = typename GetType<Index, Types...>::Type;
		constexpr size_t offset = KEMemory::getOffset<Index, Types...>();
		return reinterpret_cast<CurrentType*>(_storage + offset);
	}

	template<typename ...Types>
	void OptionalValue<Types...>::dispose()
	{
		if (_storage)
		{
			release();
			KEMemory::aligendFree(_storage);
			_storage = nullptr;
		}
	}

	template<typename ...Types>
	void OptionalValue<Types...>::release()
	{
		if (_hasValue) releaseUnsafe();
	}

	template<typename ...Types>
	void OptionalValue<Types...>::releaseUnsafe()
	{
		_hasValue = false;
		destruct<0>();
	}

	template<typename ...Types>
	void OptionalValue<Types...>::InitializeStorage()
	{
		if (_storage) KEMemory::aligendFree(_storage);
		_storage = reinterpret_cast<byte*>(KEMemory::aligendMalloc<Types...>(1));
	}

	template<typename ...Types>
	template<size_t Index, typename T>
	void OptionalValue<Types...>::construct(T&& value)
	{
		using CurrentType = typename GetType<Index, Types...>::Type;
		constexpr size_t offset = KEMemory::getOffset<Index, Types...>();
		new (_storage + offset) CurrentType(forward<CurrentType>(value));
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
		if constexpr (Index < sizeof...(Types))
		{
			using CurrentType = typename GetType<Index, Types...>::Type;
			constexpr size_t offset = KEMemory::getOffset<Index, Types...>();
			reinterpret_cast<CurrentType*>(_storage + offset)->~CurrentType();
			destruct<Index + 1>();
		}
	}

	template<typename ...Types>
	template<size_t Index>
	void OptionalValue<Types...>::copyFrom(const OptionalValue& other)
	{
		if constexpr (Index < sizeof...(Types))
		{
			using CurrentType = typename GetType<Index, Types...>::Type;
			constexpr size_t offset = KEMemory::getOffset<Index, Types...>();
			const CurrentType* src = reinterpret_cast<const CurrentType*>(other._storage + offset);
			new (_storage + offset) CurrentType(*src);
			copyFrom<Index + 1>(other);
		}
	}

	template<typename ...Types>
	void OptionalValue<Types...>::moveFrom(OptionalValue&& other)
	{
		dispose();
		_hasValue = other._hasValue;
		if(_hasValue)
		{
			_storage = other._storage;

			other._hasValue = false;
			other._storage = nullptr;
		}
	}
}
