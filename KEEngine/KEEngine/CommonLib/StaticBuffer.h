#pragma once
#include "IBuffer.h"

namespace ke
{
	constexpr size_t BUFFER_BYTES_256 = 256;
	constexpr size_t BUFFER_BYTES_1KB = 1024;
	constexpr size_t BUFFER_BYTES_2KB = 2048;
	constexpr size_t BUFFER_BYTES_4KB = 4096;

	template<size_t Size>
	class StaticBuffer : public IBuffer
	{
	public:
		StaticBuffer() = default;
		~StaticBuffer() override = default;

	public:
		char _buffer[Size] = { 0 };

	public:
		virtual void		write(const void* const input, size_t count) override;
		virtual void		writeOne(char input) override;
		virtual char*		getBuffer() override;
		virtual const char* getConstBuffer() const override;
		virtual size_t		getAvailableSize() const override;
	};
}

#include "StaticBuffer.hpp"