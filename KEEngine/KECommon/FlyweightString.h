#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
	public:
		DELETE_CONSTRUCTOR(FlyweightString);
		FlyweightString(const CharType* str);

	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;
}

#include "FlyweightString.hpp"