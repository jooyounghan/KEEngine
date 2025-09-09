#pragma once
#include "OwnedString.h"
#include "StringHelper.h"

namespace ke
{
	template<typename CharType>
	OwnedString<CharType>::OwnedString(const CharType* str)
	{
		const size_t length = StringLengthHelper<CharType>::length(str);
		__super::_count = length + 1;
		__super::_data = reinterpret_cast<CharType*>(KEMemory::aligendMalloc<false, CharType>(__super::_count));
		StringManipulateHelper<CharType>::copy(__super::_data, __super::_count, str);
	}

	template<typename CharType>
	bool OwnedString<CharType>::operator==(const OwnedString& other) const
	{
		if (__super::_count != other._count)
			return false;


		// TODO : Optimize with SIMD
		size_t targetIndex = 0;
		while (targetIndex != __super::_count)
		{
			if (__super::_data[targetIndex] != other._data[targetIndex]) return false;
			++targetIndex;
		}

		return true;
	}

	template<typename CharType>
	const CharType* OwnedString<CharType>::c_str() const&
	{
		return __super::_data;
	}

	template<typename CharType>
	void OwnedString<CharType>::append(const CharType* const str)
	{
		const size_t length = StringLengthHelper<CharType>::length(str);

		CharType* newData = reinterpret_cast<CharType*>(KEMemory::aligendMalloc<false, CharType>(__super::_count + length));

		if (__super::_count > 0)
		{
			StringManipulateHelper<CharType>::copy(newData, __super::_count, __super::_data);
			StringManipulateHelper<CharType>::copy(newData + __super::_count - 1, length, str);
			__super::_count += length;
		}
		else
		{
			StringManipulateHelper<CharType>::copy(newData, length + 1, str);
			__super::_count = length + 1;
		}

		KEMemory::aligendFree(__super::_data);
		__super::_data = newData;
 
	}

	template<typename CharType>
	void OwnedString<CharType>::append(const OwnedString& staticString)
	{
		append(staticString.c_str());
	}
}
