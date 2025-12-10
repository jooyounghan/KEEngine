#pragma once
#include "Hash.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
	public:
		explicit FlyweightString(const CharType* str);
		explicit FlyweightString(const std::basic_string<CharType>& str);

	private:
		static std::unordered_map<std::basic_string_view<CharType>, size_t, Hash<std::basic_string_view<CharType>>>& getStringEntryMap();
		static std::vector<std::basic_string<CharType>>& getStringVector();
		static const CharType* getFromEntryIndex(size_t entryIndex);

	private:
		void registerString(const CharType* str);

	private:
		size_t _entryIndex = INVALID_INDEX(size_t);

	public:
		const CharType* c_str() const { return _entryIndex != INVALID_INDEX(size_t) ? getStringVector()[_entryIndex].c_str() : nullptr; }
		size_t			getEntryIndex() const { return _entryIndex; }

	public:
		bool operator==(const FlyweightString<CharType>& other) const;
	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;

	DECLARE_TEMPLATED_HASH_SPECIALIZATION(FlyweightString, char);
}