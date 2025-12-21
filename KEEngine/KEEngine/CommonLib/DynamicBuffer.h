#pragma once
#include "IBuffer.h"

namespace ke
{
	class DynamicBuffer : public IBuffer
	{
	public:
		DynamicBuffer() = default;
		~DynamicBuffer() override = default;

	public:
		char* _buffer = nullptr;
		size_t _capacity = 0;


	public:
		virtual void		write(const void* const input, size_t count) override;
		virtual void		writeOne(char input) override;
		virtual char*		getBuffer() override;
		virtual const char* getConstBuffer() const override;
		virtual size_t		getAvailableSize() const override;

	public:
		void set(size_t size);
		void reset();
		void clear();
	};
}