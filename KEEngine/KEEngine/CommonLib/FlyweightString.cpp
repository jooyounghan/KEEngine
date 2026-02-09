#include "CommonLibPch.h"
#include "FlyweightString.h"

using namespace std;

namespace ke
{
	template<typename CharType>
	unordered_map<basic_string_view<CharType>, size_t, HASH(std::basic_string_view<CharType>)>& FlyweightString<CharType>::getStringEntryMap()
	{
		static unordered_map<basic_string_view<CharType>, size_t, HASH(std::basic_string_view<CharType>)> instance;
		return instance;
	}

	template<typename CharType>
	OwnerVector<std::basic_string<CharType>>& FlyweightString<CharType>::getStringVector()
	{
		static OwnerVector<std::basic_string<CharType>> instance;
		return instance;
	}

	template<typename CharType>
	const CharType* FlyweightString<CharType>::getFromEntryIndex(size_t entryIndex)
	{
		const OwnerVector<std::basic_string<CharType>>& stringVector = getStringVector();
		return stringVector.size() > entryIndex ? stringVector[entryIndex]->c_str() : nullptr;
	}

	template<typename CharType>
	void FlyweightString<CharType>::registerString(const std::basic_string_view<CharType>& stringView)
	{
		unordered_map<basic_string_view<CharType>, size_t, HASH(std::basic_string_view<CharType>)>& stringEntryMap = FlyweightString<CharType>::getStringEntryMap();
		OwnerVector<std::basic_string<CharType>>& stringVector = FlyweightString<CharType>::getStringVector();

		auto it = stringEntryMap.find(stringView);
		if (stringEntryMap.find(stringView) == stringEntryMap.end())
		{
			_entryIndex = stringVector.size();

			std::basic_string<CharType> str(stringView.data(), stringView.length());
			stringVector.push_back(std::move(str));
			stringEntryMap.emplace(stringView, _entryIndex);
		}
		else
		{
			_entryIndex = it->second;
		}
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString()
	{
		registerString(std::basic_string_view<CharType>(""));
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const CharType* str)
	{
		registerString(std::basic_string_view<CharType>(str));
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const basic_string<CharType>& str)
	{
		registerString(std::basic_string_view<CharType>(str.data(), str.length()));
	}

	template<typename CharType>
	FlyweightString<CharType>::FlyweightString(const std::basic_string_view<CharType>& stringView)
	{
		registerString(stringView);
	}

	template<typename CharType>
	bool FlyweightString<CharType>::operator==(const FlyweightString<CharType>& other) const
	{
		return _entryIndex == other._entryIndex;
	}

	template<typename CharType>
	bool FlyweightString<CharType>::operator!=(const FlyweightString<CharType>& other) const
	{
		return _entryIndex != other._entryIndex;
	}

#define COMPARE_STRINGS(OP)																	\
		std::basic_string_view<CharType> thisStr(getFromEntryIndex(_entryIndex));			\
		std::basic_string_view<CharType> otherStr = getFromEntryIndex(other._entryIndex);	\
		return thisStr OP otherStr;

	template<typename CharType>
	bool FlyweightString<CharType>::operator<(const FlyweightString<CharType>& other) const
	{
		COMPARE_STRINGS(<);
	}

	template<typename CharType>
	bool FlyweightString<CharType>::operator<=(const FlyweightString<CharType>& other) const
	{
		COMPARE_STRINGS(<=);
	}

	template<typename CharType>
	bool FlyweightString<CharType>::operator>(const FlyweightString<CharType>& other) const
	{
		COMPARE_STRINGS(>);
	}

	template<typename CharType>
	bool FlyweightString<CharType>::operator>=(const FlyweightString<CharType>& other) const
	{
		COMPARE_STRINGS(>=);
	}
#undef COMPARE_STRINGS

	template<>
	size_t Hash<FlyweightStringA>::convertToHash(const FlyweightStringA& value)
	{
		return value.getEntryIndex();
	}

	template<>
	size_t Hash<FlyweightStringW>::convertToHash(const FlyweightStringW& value)
	{
		return value.getEntryIndex();
	}

	template class FlyweightString<char>;
	template class FlyweightString<wchar_t>;
}

namespace std
{
	template<>
	struct hash<ke::FlyweightStringA> 
	{
		size_t operator()(const ke::FlyweightStringA& value) const noexcept 
		{
			return value.getEntryIndex();
		}
	};

	template<>
	struct hash<ke::FlyweightStringW>
	{
		size_t operator()(const ke::FlyweightStringW& value) const noexcept
		{
			return value.getEntryIndex();
		}
	};
}