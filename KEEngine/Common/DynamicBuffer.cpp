#include "DynamicBuffer.h"

namespace ke
{
	void DynamicBuffer::write(const void* const input, size_t count)
	{
		const size_t requiredSize = _cursorPos + count;
		if (_buffer.capacity() < requiredSize)
		{
			_buffer.resize(requiredSize);
		}
		memcpy(&_buffer[_cursorPos], input, count);
	}

	void DynamicBuffer::writeOne(char input)
	{
		_buffer.pushBack(input);
		++_cursorPos;
	}

	const char* DynamicBuffer::getBuffer() const
	{
		return _buffer.data();
	}
}