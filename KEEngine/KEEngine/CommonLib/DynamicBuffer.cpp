#include "CommonLibPch.h"
#include "BufferImplement.h"
#include "DynamicBuffer.h"

namespace ke
{
	void DynamicBuffer::write(const void* const input, size_t count)
	{
		WRITE_IMPLEMENT(DynamicBuffer, _capacity, count);
	}

	void DynamicBuffer::writeOne(char input)
	{
		WRITEONE_IMPLEMENT(DynamicBuffer, _capacity);
	}

	char* DynamicBuffer::getBuffer()
	{
		return GETBUFFER_IMPLEMENT();
	}

	const char* DynamicBuffer::getConstBuffer() const
	{
		return GETCONSTBUFFER_IMPLEMENT();
	}
	size_t DynamicBuffer::getAvailableSize() const
	{
		return GETAVAILABLESIZE_IMPLEMENT(_capacity);
	}

	void DynamicBuffer::set(size_t size)
	{
	}

	void DynamicBuffer::reset()
	{
	}
	
	void DynamicBuffer::clear()
	{
	}
}
