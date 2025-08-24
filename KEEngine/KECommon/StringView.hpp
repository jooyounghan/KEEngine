#pragma once
#include "StringView.h"
#include "StringHelper.h"

namespace ke
{
	template<typename CharType>
	StringView<CharType>::StringView(const CharType* str)
		: _data(str), _length(StringLengthHelper<CharType>::length(str))
	{
	}

	template<typename CharType>
	bool StringView<CharType>::operator==(const StringView& other) const
	{
		if (_length != other._length)
			return false;

		// TODO : Optimize with SIMD
		size_t targetIndex = 0;
		while (targetIndex != _length)
		{
			if (_data[targetIndex] != other._data[targetIndex]) return false;
			++targetIndex;
		}

		return true;
	}

	// Specialization HashGenerator for StringView<char>
	template<typename T>
	class HashGenerator;

	template<>
	size_t HashGenerator<StringView<char>>::convertToHash(const StringView<char>& value)
	{
		return convertToHash(value.data());
	}
}
