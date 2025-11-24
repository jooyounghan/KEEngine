#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"

#include "Vector.h"
#include "HashContainer.h"
#include "StringView.h"
#include "OwnedString.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
	public:
		DEFAULT_CONSTRUCTOR(FlyweightString);
		FlyweightString(const CharType* str);
		FlyweightString(const OwnedString<CharType>& str);

	private:
		static LargeBinHoodHashMap<StringView<CharType>, size_t, HashGenerator<StringView<CharType>>>& getStringEntryMap();
		static Vector<OwnedString<CharType>>& getStringVector();

	public:
		static const CharType* getFromEntryIndex(size_t entryIndex);

	private:
		size_t _entryIndex = INVALID_INDEX(size_t);

	public:
		const CharType* c_str() const { return _entryIndex != INVALID_INDEX(size_t) ? getStringVector()[_entryIndex].c_str() : nullptr; }

	public:
		bool operator==(const FlyweightString<CharType>& other) const;

	public:
		size_t			getEntryIndex() const { return _entryIndex; }
	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;

	DECLARE_TEMPLATED_HASH_SPECIALIZATION(FlyweightString, char);
}

#include "FlyweightString.hpp"