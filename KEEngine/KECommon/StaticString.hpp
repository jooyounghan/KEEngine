#pragma once
#include "StaticString.h"

namespace ke
{
	template<typename CharType, typename Alloc>
	inline StaticString<CharType, Alloc>::StaticString(const CharType* str)
	{
		size_t len = StringLengthHelper<CharType>::length(str);
		_memoryEntry = _allocator.allocate(len + 1);

		CharType* dest = reinterpret_cast<CharType*>(_memoryEntry._address);
		StringCopyHelper<CharType>::copy(dest, _memoryEntry._capacity, str);

#ifdef _DEBUG
		_length = len;
		_stringValuePtr = dest;
#endif
	}

	template<typename CharType, typename Alloc>
	inline StaticString<CharType, Alloc>::~StaticString()
	{
		_allocator.deallocate(_memoryEntry);
	}

	template<typename CharType, typename Alloc>
	inline const CharType* StaticString<CharType, Alloc>::c_str() const&
	{
		return reinterpret_cast<const CharType*>(_memoryEntry._address);
	}
}
