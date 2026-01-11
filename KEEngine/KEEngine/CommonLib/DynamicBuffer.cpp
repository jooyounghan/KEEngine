#include "CommonLibPch.h"
#include "DynamicBuffer.h"
#include "BufferImplement.h"
#include "MemoryUtil.h"

namespace ke
{
	DynamicBuffer::~DynamicBuffer()
	{
		release();
	}

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
		release();
		_buffer = static_cast<char*>(MemoryUtil::alignedMalloc<true, char>(size));
		_capacity = size;
	}

	void DynamicBuffer::release()
	{
		if (_buffer != nullptr)
		{
			MemoryUtil::alignedFree(_buffer);
			_buffer = nullptr;
		}
		_capacity = 0;
	}
}
