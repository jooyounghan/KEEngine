#pragma once
#include "FlyweightString.h"
#include "HashMap.h"

namespace ke
{
	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const CharType* str)
	{
		static CompactHashMap<CharType, int, HashGenerator<int>> test;
		test.insert(*str, 0);
	}
}