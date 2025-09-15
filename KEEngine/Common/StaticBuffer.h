#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<size_t Size>
	class StaticBuffer
	{
	public:
		StaticBuffer() = default;
		~StaticBuffer() = default;

	public:
		uint8 _buffer[Size] = { NULL };
		size_t _count = 0;

	public:
		void write(const void* const input, size_t count);
		inline void reset() { return _count = 0; }

	public:
		inline size_t getCount() const { return _count; }
		inline uint8* getBuffer() { return _buffer; }
	};
}

#include "StaticBuffer.hpp"