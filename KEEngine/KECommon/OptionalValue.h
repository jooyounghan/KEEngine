#pragma once
#include "MemoryCommon.h"
#include "TypeTraits.h"

namespace ke
{
#pragma region OptionalValue
	template<size_t Index, typename T, typename... Ts>
	struct GetType {
		using type = typename GetType<Index - 1, Ts...>::type;
	};

	template<typename T, typename... Ts>
	struct GetType<0, T, Ts...> 
	{
		using type = T;
	};

	template<size_t Index, typename T, typename... Ts>
	struct GetOffset 
	{
		static constexpr size_t value = sizeof(T) + GetOffset<Index - 1, Ts...>::value;
	};

	template<typename T, typename... Ts>
	struct GetOffset<0, T, Ts...> 
	{
		static constexpr size_t value = 0;
	};

	template<typename... Types>
	class OptionalValue
	{
		static_assert(sizeof...(Types) > 0, "OptionalTuple must have at least one type");

	public:
		OptionalValue() = default;
		OptionalValue(const Types&... value);
		OptionalValue(Types&&... value);
		OptionalValue(const OptionalValue& other);
		OptionalValue(OptionalValue&& other);
		~OptionalValue();

	public:
		OptionalValue& operator=(const OptionalValue& other);
		OptionalValue& operator=(OptionalValue&& other);

	public:
		void setValue(const Types&... value);
		void setValue(Types&&... value);
		bool hasValue() const;

	public:
		template<size_t Index>
		auto* tryGetValue();
		template<size_t Index>
		void setValue(const GetType<Index, Types...>::type& value);
		template<size_t Index>
		void setValue(GetType<Index, Types...>::type&& value);

	private:
		template<size_t Index, typename T>
		void construct(T&& value);
		template<size_t Index, typename T, typename... Ts>
		void construct(T&& first, Ts&&... rest);
		template<size_t Index>
		void destruct();
		template<size_t Index>
		void copyFrom(const OptionalValue& other);
		template<size_t Index>
		void moveFrom(OptionalValue&& other);

	private:
		bool _hasValue = false;
		alignas(KEMemory::memoryAlignOf<Types...>()) uint8 _storage[KEMemory::getSizeOfN<Types...>(1)];
	};
#pragma endregion

}

#include "OptionalValue.hpp"