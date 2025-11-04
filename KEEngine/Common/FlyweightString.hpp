#pragma once
#include "FlyweightString.h"

namespace ke
{
	template<typename CharType>
	LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& FlyweightString<CharType>::getStringEntryMap()
	{
		static LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>> instance;
		return instance;
	}

	template<typename CharType>
	Vector<OwnedString<CharType>>& FlyweightString<CharType>::getStringVector()
	{
		static Vector<OwnedString<CharType>> instance;
		return instance;
	}

	template<typename CharType>
	const CharType* FlyweightString<CharType>::getFromEntryIndex(size_t entryIndex)
	{
		const Vector<OwnedString<CharType>>& stringVector = getStringVector();
		return stringVector.size() > entryIndex ? stringVector[entryIndex].c_str() : nullptr;
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const CharType* str)
	{
		LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& stringEntryMap = getStringEntryMap();
		Vector<OwnedString<CharType>>& stringVector = getStringVector();

		StringView<CharType> stringView = StringView<CharType>(str);

		HashBucketFindResult<StringView<CharType>, size_t> findResult = stringEntryMap.find(stringView);
		size_t* foundVectorIndex = findResult._valuePtr;
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
	FlyweightString<CharType>::FlyweightString(const OwnedString<CharType>& str)
	{
		LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& stringEntryMap = getStringEntryMap();
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

	template<typename CharType>
	bool FlyweightString<CharType>::operator==(const FlyweightString<CharType>& other) const
	{
		return _entryIndex == other._entryIndex;
	}
}