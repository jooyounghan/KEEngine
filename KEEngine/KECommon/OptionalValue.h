#pragma once
#include "MemoryCommon.h"
#include "TypeTraits.h"

namespace ke
{
#pragma region OptionalValue
	template<typename... Types>
	class OptionalValue
	{
	public:
		OptionalValue();
		OptionalValue(const Types&... value);
		OptionalValue(Types&&... value);
		OptionalValue(const OptionalValue& other);
		OptionalValue(OptionalValue&& other);

	public:
		virtual ~OptionalValue();

	public:
		OptionalValue& operator=(const OptionalValue& other);
		OptionalValue& operator=(OptionalValue&& other);

	public:
		template<size_t Index>
		auto* tryGetValue();

	public:
		bool hasValue() const;
		void setValue(const Types&... value);
		void setValue(Types&&... value);

	public:
		void dispose();
		void release();
		void releaseUnsafe();

	private:
		void InitializeStorage();
		template<size_t Index, typename T>
		void construct(T&& value);
		template<size_t Index, typename T, typename... Ts>
		void construct(T&& first, Ts&&... rest);
		template<size_t Index>
		void destruct();
		template<size_t Index>
		void copyFrom(const OptionalValue& other);
		void moveFrom(OptionalValue&& other);


	protected:
		bool _hasValue;
		alignas(KEMemory::alignOf<Types...>()) byte* _storage = nullptr;

		// Static Asserts
		static_assert(sizeof...(Types) > 0, "OptionalTuple must have at least one type");
	};
#pragma endregion

}

#include "OptionalValue.hpp"