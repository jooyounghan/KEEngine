#pragma once
#include "OwnedString.h"

namespace ke
{
	template<typename CharType, size_t CharCount>
	class BoundedString
	{
		static_assert(CharCount > 1, "CharCount must be greater than 1");
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");

	public:
		BoundedString() = default;
		BoundedString(const CharType* str);
		BoundedString(const BoundedString& boundedString);
		BoundedString(BoundedString&& boundedString) noexcept;
		~BoundedString();

	public:
		const CharType* c_str() const&;
		const CharType* c_str() const&& = delete;

	public:
		void append(const CharType* const str);
		template<typename Alloc>
		void append(const OwnedString<CharType, Alloc>& ownedString);

	public:
		size_t length() const { return _length; }
		constexpr size_t capacity() const { return CharCount; }

	protected:
		CharType*	_buffer = nullptr;
		size_t		_length = 0;

#ifdef _DEBUG
	private:
		size_t		_capacity = 0;
#endif
	};

	template<size_t CharCount>
	using BoundedStringA = BoundedString<char, CharCount>;
	template<size_t CharCount>
	using BoundedStringW = BoundedString<wchar_t, CharCount>;
}

#include "BoundedString.hpp"