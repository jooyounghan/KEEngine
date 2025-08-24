#pragma once
#include "FlyweightString.h"
#include "OwnedString.h"
#include "HashSet.h"

namespace ke
{
	template<typename CharType>
	CompactHashSet<StringView<CharType>, HashGenerator<StringView<CharType>>>& FlyweightString<CharType>::getStringEntrySet()
	{
		static CompactHashSet<StringView<CharType>, HashGenerator<StringView<CharType>>> instance;
		return instance;
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const CharType* str)
	{
		// 여기서 str는 버퍼가 될 수도 있고 정말 리터럴 일 수도 있음... 수정 필요
		CompactHashSet<StringView<CharType>, HashGenerator<StringView<CharType>>>& stringEntrySet = getStringEntrySet();
		
		StringView<CharType> stringView = StringView<CharType>(str);
		StringView<CharType>* foundResult = stringEntrySet.find(stringView);

		if (foundResult == nullptr)
		{
			stringEntrySet.insert(stringView);
		}

		_data = str;
	}
}