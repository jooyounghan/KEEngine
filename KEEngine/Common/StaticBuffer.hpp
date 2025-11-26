#pragma once
#include "StaticBuffer.h"
#include "MathCommon.h"

namespace ke
{
	template<size_t Size>
	void StaticBuffer<Size>::write(const void* const input, size_t count)
	{
		KE_DEBUG_ASSERT(Size - _cursorPos > 0, "StaticBuffer overflow: not enough space to write data.");

		count = KEMath::min(count, Size - _cursorPos);
		memcpy(&_buffer[_cursorPos], input, count);
		_cursorPos += count;
	}

	template<size_t Size>
	void StaticBuffer<Size>::writeOne(char input)
	{
		KE_DEBUG_ASSERT(Size - _cursorPos > 0, "StaticBuffer overflow: not enough space to write data.");
		if (_cursorPos < Size) _buffer[_cursorPos++] = input;
	}

	template<size_t Size>
	const char* StaticBuffer<Size>::getBuffer() const 
	{
		return _buffer; 
	}
}