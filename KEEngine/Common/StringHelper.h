#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<typename CharType>
	struct StringLengthHelper
	{
		static size_t length(const CharType* str);
	};

	template<typename CharType>
	struct StringManipulateHelper
	{
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
		static void copy(CharType* dest, size_t destBufferSize, const CharType* src);
		static void clear(CharType* dest, size_t destBufferSize);
	};
}

#include "StringHelper.hpp"