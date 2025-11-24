#pragma once
#include "TypeTraits.h"

namespace ke
{
	template<typename CharType>
	class StringView
	{
	public:
		StringView() = default;
		StringView(const CharType* str);
		StringView(const CharType* str, size_t length);
		StringView(const StringView& other) = default;
		StringView(StringView&& other) noexcept = default;

	public:
		~StringView() = default;

	public:
		StringView& operator=(const StringView& other) = default;
		StringView& operator=(StringView&& other) noexcept = default;

	public:
		bool operator==(const StringView& other) const;

	public:
		inline const CharType* data() const { return _data; }
		inline size_t length() const { return _length; }

	private:
		const CharType* _data = nullptr;
		size_t			_length = 0;

		// Static Asserts
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};
	using StringViewA = StringView<char>;
	using StringViewW = StringView<wchar_t>;
}

#include "StringView.hpp"