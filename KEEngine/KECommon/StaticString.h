#pragma once
#include "TypeCommon.h"
#include "TypeTraits.h"

namespace ke
{
	template<typename CharType>
	class StaticString
	{
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};

	using StaticStringA = StaticString<char>;
	using StaticStringW = StaticString<wchar_t>;
}
