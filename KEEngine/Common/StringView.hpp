#pragma once
#include "StringView.h"
#include "StringHelper.h"
#include "HashGenerator.h"

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

	DECLARE_TEMPLATED_HASH_SPECIALIZATION(StringView, char);
}
