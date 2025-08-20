#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"
#include "HashMap.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
	public:
		DELETE_CONSTRUCTOR(FlyweightString);
		FlyweightString(const CharType* str);

	public:
		~FlyweightString();

	private:


	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;
}