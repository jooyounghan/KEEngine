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
		// ���⼭ str�� ���۰� �� ���� �ְ� ���� ���ͷ� �� ���� ����... ���� �ʿ�
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