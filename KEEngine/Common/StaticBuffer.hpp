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
}