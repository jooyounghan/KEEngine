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
		virtual void		write(const void* const input, size_t count) = 0;
		virtual void		writeOne(char input) = 0;
		virtual const char* getBuffer() = 0;

	public:
		inline void			reset() { _count = 0; }
		inline size_t		getCount() const { return _count; }
	};

	template<size_t Size>
	class StaticBuffer : public IStaticBuffer
	{
	public:
		StaticBuffer() = default;
		~StaticBuffer() override = default;

	public:
		char _buffer[Size] = { NULL };

	public:
		virtual void write(const void* const input, size_t count) override;
		virtual void writeOne(char input) override;

	public:
		inline const char* getBuffer() override { return _buffer; }
	};
}

#include "StaticBuffer.hpp"