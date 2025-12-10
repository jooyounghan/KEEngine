#pragma once
#include "TypeTraits.h"
#include "LinearContainer.h"
#include "HashGenerator.h"

namespace ke
{
	template<typename CharType>
	class OwnedString : public LinearContainer<CharType, 0>
	{
	public:
		DEFAULT_CONSTRUCTOR(OwnedString);
		~OwnedString() = default;

	public:
		OwnedString(const CharType* str);
		OwnedString(const CharType* const ptr, size_t length);

	public:
		bool operator==(const OwnedString& other) const;

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

	DECLARE_TEMPLATED_HASH_SPECIALIZATION(OwnedString, char);
}

#include "OwnedString.hpp"