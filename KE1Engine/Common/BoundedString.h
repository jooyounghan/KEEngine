#pragma once
#include "OwnedString.h"

namespace ke
{
	template<typename CharType, size_t CharCount>
	class BoundedString : public LinearContainer<CharType, CharCount>
	{

	public:
		BoundedString() = default;
		BoundedString(const CharType* str);
		BoundedString(const BoundedString& other) = default;
		BoundedString(BoundedString&& other) noexcept = default;

	public:
		~BoundedString() = default;

	public:
		BoundedString& operator=(const BoundedString& other) = default;
		BoundedString& operator=(BoundedString&& other) noexcept = default;

	public:
		const CharType* c_str() const&;
		const CharType* c_str() const&& = delete;

	public:
		void append(const CharType* const str);
		template<typename Alloc>
		void append(const OwnedString<CharType>& ownedString);

	public:
		size_t length() const { return _length; }

	protected:
		size_t		_length = 0;

		// Static Asserts
		static_assert(CharCount > 1, "CharCount must be greater than 1");
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};
		
	template<size_t CharCount>
	using BoundedStringA = BoundedString<char, CharCount>;
	template<size_t CharCount>
	using BoundedStringW = BoundedString<wchar_t, CharCount>;
}

#include "BoundedString.hpp"