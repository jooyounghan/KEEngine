#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<typename CharType>
	struct StringLengthHelper
	{
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};

	template<>
	struct StringLengthHelper<char>
	{
		static size_t length(const char* str) { return strlen(str); }
	};

	template<>
	struct StringLengthHelper<wchar_t>
	{
		static size_t length(const wchar_t* str) { return wcslen(str); }
	};

	template<typename CharType>
	struct StringCopyHelper
	{
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
		static void copy(CharType* dest, size_t destBufferSize, const CharType* src)
		{
			size_t len = StringLengthHelper<CharType>::length(src);
			if (len >= destBufferSize)
				len = destBufferSize - 1;

			memcpy(dest, src, len * sizeof(CharType));
			dest[len] = '\0';
		}
	};
}