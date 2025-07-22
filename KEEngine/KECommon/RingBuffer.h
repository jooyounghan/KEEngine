#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<typename T, size_t Size>
	class RingBuffer
	{
	public:
		RingBuffer();
		~RingBuffer();

	public:
		bool pushBack(KE_IN const T& item);
		bool pushBack(KE_IN T&& item);
		bool popFront(KE_OUT T& item);

	public:
		inline size_t size() const { return _count; }
		inline size_t capacity() const { return Size; }
		inline bool isEmpty() const { return _count == 0; }
		inline bool isFull() const { return _count == Size; }

	private:
		alignas(T) uint8 _buffer[sizeof(T) * Size];
		size_t _head;
		size_t _tail;
		size_t _count;

#ifdef _DEBUG
	private:
		const T* _valuePtr = reinterpret_cast<T*>(&_buffer);
#endif
	};
}

#include "RingBuffer.hpp"