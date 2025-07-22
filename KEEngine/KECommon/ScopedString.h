#pragma once
#include "TypeCommon.h"
#include "TypeTraits.h"

namespace ke
{
	template<typename CharType, size_t BufferSize>
	class ScopedString
	{
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};

	template<size_t BufferSize>
	using ScopedStringA = ScopedString<char, BufferSize>;
	template<size_t BufferSize>
	using ScopedStringW = ScopedString<wchar_t, BufferSize>;
}

