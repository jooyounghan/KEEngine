#pragma once
#include "TypeCommon.h"

namespace ke
{
	class IStaticBuffer
	{
	public:
		virtual ~IStaticBuffer() = default;

	protected:
		size_t _count = 0;

	public:
		virtual void	write(const void* const input, size_t count) = 0;
		virtual void	writeOne(uint8 input) = 0;
		inline void reset() { _count = 0; }

	public:
		inline size_t getCount() const { return _count; }
		virtual uint8* getBuffer() = 0;
	};

	template<size_t Size>
	class StaticBuffer : public IStaticBuffer
	{
	public:
		StaticBuffer() = default;
		~StaticBuffer() override = default;

	public:
		uint8 _buffer[Size] = { NULL };

	public:
		virtual void write(const void* const input, size_t count) override;
		virtual void writeOne(uint8 input) override;

	public:
		inline uint8* getBuffer() override { return _buffer; }
	};
}

#include "StaticBuffer.hpp"