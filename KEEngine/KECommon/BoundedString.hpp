#pragma once
#include "BoundedString.h"
#include "MemoryCommon.h"

namespace ke
{
	template<typename CharType, size_t CharCount>
	inline BoundedString<CharType, CharCount>::BoundedString(const CharType* str)
	{
		_buffer = reinterpret_cast<CharType*>(KEMemory::aligendMalloc<CharType>(CharCount));

		size_t strCapacity = StringLengthHelper<CharType>::length(str) + 1;
		strCapacity = (strCapacity >= CharCount) ? CharCount : strCapacity;
		StringManipulateHelper<CharType>::copy(_buffer, CharCount, str);
		_length = strCapacity - 1;

#ifdef _DEBUG
		_capacity = CharCount;
#endif
	}

	template<typename CharType, size_t CharCount>
	inline BoundedString<CharType, CharCount>::BoundedString(const BoundedString& boundedString)
	{
		_buffer = reinterpret_cast<CharType*>(KEMemory::aligendMalloc<CharType>(CharCount));
		StringManipulateHelper<CharType>::copy(_buffer, CharCount, boundedString.c_str());
		_length = boundedString._length;

#ifdef _DEBUG
		_capacity = CharCount;
#endif
	}

	template<typename CharType, size_t CharCount>
	inline BoundedString<CharType, CharCount>::BoundedString(BoundedString&& boundedString) noexcept
	{
		_length = boundedString._length;
		_buffer = boundedString._buffer;
		boundedString._buffer = nullptr;

#ifdef _DEBUG
		_capacity = CharCount;
#endif
	}

	template<typename CharType, size_t CharCount>
	inline BoundedString<CharType, CharCount>::~BoundedString()
	{
		if (_buffer != nullptr)
		{
			_aligned_free(_buffer);
			_buffer = nullptr;
		}
	}

	template<typename CharType, size_t CharCount>
	inline const CharType* BoundedString<CharType, CharCount>::c_str() const&
	{
		return _buffer;
	}

	template<typename CharType, size_t CharCount>
	inline void BoundedString<CharType, CharCount>::append(const CharType* const str)
	{
		size_t strCapacity = StringLengthHelper<CharType>::length(str) + 1;
		const size_t availableCapacity = CharCount - _length;
		strCapacity = (strCapacity >= availableCapacity) ? availableCapacity : strCapacity;

		if (strCapacity <= 1) return;

		StringManipulateHelper<CharType>::copy(_buffer + _length, strCapacity, str);
		_length += (strCapacity - 1);
	}

	template<typename CharType, size_t CharCount>
	template<typename Alloc>
	inline void BoundedString<CharType, CharCount>::append(const OwnedString<CharType, Alloc>& ownedString)
	{
		const CharType* str = ownedString.c_str();
		append(str);
	}

}