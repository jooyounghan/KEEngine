#pragma once
#include "BoundedString.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename CharType, size_t CharCount>
	BoundedString<CharType, CharCount>::BoundedString(const CharType* str)
		: LinearContainer<CharType, CharCount>()
	{
		constexpr size_t strCapacity = CharCount - 1;

		_length = StringLengthHelper<CharType>::length(str);
		_length = (_length > strCapacity) ? strCapacity : _length;

		StringManipulateHelper<CharType>::copy(__super::_data, _length + 1, str);
	}

	template<typename CharType, size_t CharCount>
	const CharType* BoundedString<CharType, CharCount>::c_str() const&
	{
		return __super::_data;
	}

	template<typename CharType, size_t CharCount>
	void BoundedString<CharType, CharCount>::append(const CharType* const str)
	{
		const size_t availableCapacity = CharCount - _length;

		size_t appendLength = StringLengthHelper<CharType>::length(str);
		appendLength = (appendLength > availableCapacity) ? availableCapacity : appendLength;

		StringManipulateHelper<CharType>::copy(__super::_data + _length, appendLength + 1, str);
		_length += appendLength;
	}

	template<typename CharType, size_t CharCount>
	template<typename Alloc>
	void BoundedString<CharType, CharCount>::append(const OwnedString<CharType>& ownedString)
	{
		append(ownedString.c_str());
	}

}