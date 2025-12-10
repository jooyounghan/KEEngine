#pragma once
#include "pch.h"
#include "MathUtil.h"
#include "StaticBuffer.h"

namespace ke
{
	template<size_t Size>
	void StaticBuffer<Size>::write(const void* const input, size_t count)
	{
		KE_DEBUG_ASSERT(Size - _cursorPos > 0, "StaticBuffer overflow: not enough space to write data.");

		count = MathUtil::min(count, Size - _cursorPos);
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
	char* StaticBuffer<Size>::getBuffer()
	{
		return &_buffer[0];
	}

	template<size_t Size>
	const char* StaticBuffer<Size>::getConstBuffer() const
	{
		return &_buffer[0];
	}

	template<size_t Size>
	size_t StaticBuffer<Size>::getAvailableSize() const { return Size - _cursorPos; }
}