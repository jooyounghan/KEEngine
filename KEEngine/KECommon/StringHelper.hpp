#pragma once
#include "StringHelper.h"

namespace ke
{
	inline size_t StringLengthHelper<char>::length(const char* str) { return strlen(str); }
	inline size_t StringLengthHelper<wchar_t>::length(const wchar_t* str) { return wcslen(str); }

	template<typename CharType>
	inline void StringManipulateHelper<CharType>::copy(CharType* dest, size_t destBufferSize, const CharType* src)
	{
		size_t len = StringLengthHelper<CharType>::length(src);
		if (len >= destBufferSize)
			len = destBufferSize - 1;

		memcpy(dest, src, len * sizeof(CharType));
		dest[len] = '\0';
	}

	template<typename CharType>
	inline void StringManipulateHelper<CharType>::clear(CharType* dest, size_t destBufferSize)
	{
		memset(dest, '\0', destBufferSize * sizeof(CharType));
	}

}