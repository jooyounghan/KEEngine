#pragma once
#include "StringHelper.h"

namespace ke
{
	template<typename CharType>
	inline size_t StringLengthHelper<CharType>::length(const CharType* str)
	{
		static_assert(false, "CharType only accept char, wchar_t");
	}

	template<>
	inline size_t StringLengthHelper<char>::length(const char* str) { return strlen(str); }
	template<>
	inline size_t StringLengthHelper<wchar_t>::length(const wchar_t* str) { return wcslen(str); }

	template<typename CharType>
	void StringManipulateHelper<CharType>::copy(CharType* dest, size_t destBufferSize, const CharType* src)
	{
		if (src == nullptr) return;

		size_t len = StringLengthHelper<CharType>::length(src);
		if (len >= destBufferSize)
			len = destBufferSize - 1;

		memcpy(dest, src, len * sizeof(CharType));
		dest[len] = '\0';
	}

	template<typename CharType>
	void StringManipulateHelper<CharType>::clear(CharType* dest, size_t destBufferSize)
	{
		memset(dest, '\0', destBufferSize * sizeof(CharType));
	}

}