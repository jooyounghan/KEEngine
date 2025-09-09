#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"

#include "Vector.h"
#include "HashMap.h"
#include "StringView.h"
#include "OwnedString.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
	public:
		DELETE_CONSTRUCTOR(FlyweightString);
		FlyweightString(const CharType* str);
		FlyweightString(const OwnedString<CharType>& str);

	private:
		static LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& getStringEntryMap();
		static Vector<OwnedString<CharType>>& getStringVector();

	private:
		size_t _entryIndex;

	public:
		const CharType* c_str() { return getStringVector()[_entryIndex].c_str(); }
	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;
}

#include "FlyweightString.hpp"