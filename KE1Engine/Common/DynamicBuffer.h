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
		virtual void			write(const void* const input, size_t count) override;
		virtual void			writeOne(char input) override;
		inline virtual char*	getBuffer() override { return _buffer.data(); }
		virtual size_t			getAvailableSize() const override { return _buffer.size() - _cursorPos; }

	public:
		inline void reserve(size_t newSize) { _buffer.reserve(newSize); }
		inline void resize(size_t newSize) { _buffer.resize(newSize); }
	};
}