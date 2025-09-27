#pragma once
#include "StaticBuffer.h"
#include "MathCommon.h"

namespace ke
{
	template<size_t Size>
	void StaticBuffer<Size>::write(const void* const input, size_t count)
	{
		count = KEMath::min(count, Size - _count);
		memcpy(&_buffer[_count], input, count);
		_count += count;
	}

	template<size_t Size>
	void StaticBuffer<Size>::writeOne(char input)
	{
		if (_count < Size) _buffer[_count++] = input;
	}
}