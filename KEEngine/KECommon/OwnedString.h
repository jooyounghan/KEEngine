#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"
#include "LinearContainer.h"

namespace ke
{
	template<typename CharType>
	class OwnedString : public LinearContainer<CharType, 0>
	{
	public:
		OwnedString() = default;
		OwnedString(const CharType* str);
		OwnedString(const OwnedString& other) = default;
		OwnedString(OwnedString&& other) noexcept = default;

	public:
		~OwnedString() = default;

	public:
		OwnedString& operator=(const OwnedString& other) = default;
		OwnedString& operator=(OwnedString&& other) noexcept = default;


	public:
		operator const CharType* () const = delete;
		operator const CharType* () = delete;
		operator CharType* () const = delete;
		operator CharType* () = delete;

	public:
		const CharType* c_str() const&;
		const CharType* c_str() const&& = delete;

	public:
		void append(const CharType* const str);
		void append(const OwnedString& staticString);

	public:
		size_t length() const { return __super::_count - 1; }

		// Static Asserts
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};

	using OwnedStringA = OwnedString<char>;
	using OwnedStringW = OwnedString<wchar_t>;
}

#include "OwnedString.hpp"