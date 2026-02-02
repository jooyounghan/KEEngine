#pragma once
#include "Hash.h"
#include "OwnerVector.h"

namespace ke
{
	template<typename CharType>
	class FlyweightString
	{
		DELETE_DEFAULT_CONSTRUCTOR(FlyweightString);

	public:
		FlyweightString(const CharType* str);
		FlyweightString(const std::basic_string<CharType>& str);
		FlyweightString(const std::basic_string_view<CharType>& stringView);

	private:
		static std::unordered_map<std::basic_string_view<CharType>, size_t, HASH(std::basic_string_view<CharType>)>& getStringEntryMap();
		static OwnerVector<std::basic_string<CharType>>& getStringVector();
		static const CharType* getFromEntryIndex(size_t entryIndex);

	private:
		void registerString(const std::basic_string_view<CharType>& stringView);

	private:
		size_t _entryIndex = INVALID_INDEX(size_t);

	public:
		const std::basic_string<CharType>	toString() const { return _entryIndex != INVALID_INDEX(size_t) ? *(getStringVector()[_entryIndex]) : std::basic_string<CharType>(); }
		const CharType*						c_str() const { return _entryIndex != INVALID_INDEX(size_t) ? getStringVector()[_entryIndex]->c_str() : nullptr; }
		const size_t						length() const { return _entryIndex != INVALID_INDEX(size_t) ? getStringVector()[_entryIndex]->length() : 0; }
		size_t								getEntryIndex() const { return _entryIndex; }

	public:
		bool operator==(const FlyweightString<CharType>& other) const;
		bool operator!=(const FlyweightString<CharType>& other) const;
		bool operator<(const FlyweightString<CharType>& other) const;
		bool operator<=(const FlyweightString<CharType>& other) const;
		bool operator>(const FlyweightString<CharType>& other) const;
		bool operator>=(const FlyweightString<CharType>& other) const;
	};

	using FlyweightStringA = FlyweightString<char>;
	using FlyweightStringW = FlyweightString<wchar_t>;

	DECLARE_TEMPLATED_HASH_SPECIALIZATION(FlyweightString, char);
}