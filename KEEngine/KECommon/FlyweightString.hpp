#pragma once
#include "FlyweightString.h"
#include "OwnedString.h"
#include "HashSet.h"

namespace ke
{
	template<typename CharType>
	CompactHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& FlyweightString<CharType>::getStringEntryMap()
	{
		static CompactHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>> instance;
		return instance;
	}

	template<typename CharType>
	Vector<OwnedString<CharType>>& FlyweightString<CharType>::getStringVector()
	{
		static Vector<OwnedString<CharType>> instance;
		return instance;
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const CharType* str)
	{
		CompactHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& stringEntryMap = getStringEntryMap();
		Vector<OwnedString<CharType>>& stringVector = getStringVector();

		StringView<CharType> stringView = StringView<CharType>(str);
		size_t* foundVectorIndex = stringEntryMap.find(stringView);
		if (foundVectorIndex == nullptr)
		{
			_entryIndex = stringVector.size();
			stringVector.pushBack(OwnedString(str));

			stringEntryMap.insert(stringView, _entryIndex);
		}
		else
		{
			_entryIndex = *foundVectorIndex;
		}
	}

	template<typename CharType>
	inline FlyweightString<CharType>::FlyweightString(const OwnedString<CharType>& str)
	{
		CompactHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& stringEntryMap = getStringEntryMap();
		Vector<OwnedString<CharType>>& stringVector = getStringVector();

		StringView<CharType> stringView = StringView<CharType>(str.c_str());
		size_t* foundVectorIndex = stringEntryMap.find(stringView);
		if (foundVectorIndex == nullptr)
		{
			_entryIndex = stringVector.size();
			stringVector.pushBack(str);

			stringEntryMap.insert(stringView, _entryIndex);
		}
		else
		{
			_entryIndex = *foundVectorIndex;
		}
	}
}