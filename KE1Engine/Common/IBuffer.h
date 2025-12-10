#pragma once
#include "TypeCommon.h"
#include "AssertManager.h"

namespace ke
{
	class IBuffer
	{
	public:
		virtual ~IBuffer() = default;

	protected:
		size_t _cursorPos = 0;

	public:
		virtual void		write(const void* const input, size_t count) = 0;
		virtual void		writeOne(char input) = 0;
		virtual char*		getBuffer() = 0;
		virtual size_t		getAvailableSize() const = 0;

	public:
		inline void			reset() { _cursorPos = 0; }
		inline size_t		getCursorPos() const { return _cursorPos; }		
	};
}