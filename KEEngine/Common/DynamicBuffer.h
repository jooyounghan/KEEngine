#pragma once
#include "IBuffer.h"
#include "Vector.h"

namespace ke
{
	class DynamicBuffer : public IBuffer
	{
	public:
		DynamicBuffer() = default;
		~DynamicBuffer() override = default;

	protected:
		Vector<char> _buffer;

	public:
		virtual void write(const void* const input, size_t count) override;
		virtual void writeOne(char input) override;
		virtual const char* getBuffer() const override;

	public:
		void reserve(size_t newSize);
		void resize(size_t newSize);
	};
}