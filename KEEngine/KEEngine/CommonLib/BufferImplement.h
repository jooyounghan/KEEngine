#pragma once
#include "CommonLibPch.h"
#include "MathUtil.h"

#define WRITE_IMPLEMENT(BufferClass, Size, Count)														\
	KE_DEBUG_ASSERT(Size - _cursorPos > 0, #BufferClass " overflow: not enough space to write data.");	\
	Count = MathUtil::min(Count, Size - _cursorPos);													\
	memcpy(&_buffer[_cursorPos], input, Count);															\
	_cursorPos += Count;

#define WRITEONE_IMPLEMENT(BufferClass, Size)															\
	KE_DEBUG_ASSERT(Size - _cursorPos > 0, #BufferClass " overflow: not enough space to write data.");	\
	if (_cursorPos < Size) _buffer[_cursorPos++] = input;

#define GETBUFFER_IMPLEMENT()				&_buffer[0];
#define GETCONSTBUFFER_IMPLEMENT()			&_buffer[0];
#define GETAVAILABLESIZE_IMPLEMENT(Size)	Size - _cursorPos;