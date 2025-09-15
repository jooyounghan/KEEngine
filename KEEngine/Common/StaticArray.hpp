#pragma once
#include "StaticArray.h"

namespace ke
{
	template<typename T, size_t Count>
	constexpr StaticArray<T, Count>::StaticArray()
		: _data{}
	{
	}

	template<typename T, size_t Count>
	template<typename... Args>
	constexpr StaticArray<T, Count> ::StaticArray(Args... args)
		: _data{ args }...
	{
		static_assert(sizeof...(Args) == Count, "Need exactly Count args");
	}

	template<typename T, size_t Count>
	constexpr size_t StaticArray<T, Count>::size() const { return Count; }

	template<typename T, size_t Count>
	constexpr T& StaticArray<T, Count>::operator[](size_t i) { return _data[i]; }

	template<typename T, size_t Count>
	constexpr const T& StaticArray<T, Count>::operator[](size_t i) const { return _data[i]; }
}

