#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"

#include "Vector.h"
#include "HashSet.h"
#include "StringView.h"

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
		static CompactHashSet<StringView<CharType>, HashGenerator<StringView<CharType>>>& getStringEntrySet();

	private:
		const CharType* _data = nullptr;
	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;
}

#include "FlyweightString.hpp"