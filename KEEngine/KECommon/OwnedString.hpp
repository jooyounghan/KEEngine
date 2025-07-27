#pragma once
#include "OwnedString.h"
#include "BoundedString.h"

namespace ke
{

	template<typename CharType, typename Alloc>
	inline OwnedString<CharType, Alloc>::OwnedString(const CharType* str)
	{
		const size_t len = StringLengthHelper<CharType>::length(str);
		_memoryEntry = _allocator.allocate(len + 1);

		CharType* destStr = reinterpret_cast<CharType*>(_memoryEntry._address);
		StringManipulateHelper<CharType>::copy(destStr, _memoryEntry._capacity, str);

#ifdef _DEBUG
		_length = len;
		_stringValuePtr = destStr;
#endif
	}

	template<typename CharType, typename Alloc>
	inline OwnedString<CharType, Alloc>::OwnedString(const OwnedString& staticString)
	{
		const CharType* str = staticString.c_str();
		const size_t len = StringLengthHelper<CharType>::length(str);
		_memoryEntry = _allocator.allocate(len + 1);

		CharType* destStr = reinterpret_cast<CharType*>(_memoryEntry._address);
		StringManipulateHelper<CharType>::copy(destStr, _memoryEntry._capacity, str);

#ifdef _DEBUG
		_length = len;
		_stringValuePtr = destStr;
#endif
	}

	template<typename CharType, typename Alloc>
	inline OwnedString<CharType, Alloc>::OwnedString(OwnedString&& str)
	{
		_memoryEntry = std::move(str._memoryEntry);
		str._memoryEntry._address = nullptr;
		
#ifdef _DEBUG
		_length = str._length;
		_stringValuePtr = str._stringValuePtr;
#endif
	}

	template<typename CharType, typename Alloc>
	inline OwnedString<CharType, Alloc>::~OwnedString()
	{
		_allocator.deallocate(_memoryEntry);
	}

	template<typename CharType, typename Alloc>
	inline const CharType* OwnedString<CharType, Alloc>::c_str() const&
	{
		return reinterpret_cast<const CharType*>(_memoryEntry._address);
	}

	template<typename CharType, typename Alloc>
	inline void OwnedString<CharType, Alloc>::append(const CharType* const str)
	{
		const size_t len = StringLengthHelper<CharType>::length(str);
		MemoryEntry newMemoryEntry = _allocator.allocate(_memoryEntry._capacity + len);

		const CharType* oldStr = reinterpret_cast<CharType*>(_memoryEntry._address);
		CharType* destStr = reinterpret_cast<CharType*>(newMemoryEntry._address);
		StringManipulateHelper<CharType>::copy(destStr, _memoryEntry._capacity, oldStr);
		StringManipulateHelper<CharType>::copy(destStr + (_memoryEntry._capacity - 1), newMemoryEntry._capacity, str);

		_allocator.deallocate(_memoryEntry);
		_memoryEntry = newMemoryEntry;

#ifdef _DEBUG
		_length = _length + len;
		_stringValuePtr = destStr;
#endif
	}

	template<typename CharType, typename Alloc>
	inline void OwnedString<CharType, Alloc>::append(const OwnedString& staticString)
	{
		append(staticString.c_str());
	}
}
