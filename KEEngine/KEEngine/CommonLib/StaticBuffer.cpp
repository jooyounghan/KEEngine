#include "CommonLibPch.h"
#include "BufferImplement.h"
#include "StaticBuffer.h"

namespace ke
{
	template<size_t Size>
	void StaticBuffer<Size>::write(const void* const input, size_t count)
	{
		WRITE_IMPLEMENT(StaticBuffer, Size, count);
	}

	template<size_t Size>
	void StaticBuffer<Size>::writeOne(char input)
	{
		WRITEONE_IMPLEMENT(StaticBuffer, Size);
	}

	template<size_t Size>
	char* StaticBuffer<Size>::getBuffer()
	{
		return GETBUFFER_IMPLEMENT();
	}

	template<size_t Size>
	const char* StaticBuffer<Size>::getConstBuffer() const
	{
		return GETCONSTBUFFER_IMPLEMENT();
	}

	template<size_t Size>
	size_t StaticBuffer<Size>::getAvailableSize() const
	{
		return GETAVAILABLESIZE_IMPLEMENT(Size);
	}
}