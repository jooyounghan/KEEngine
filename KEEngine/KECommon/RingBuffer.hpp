#pragma once
#include "RingBuffer.h"
#include "OverwriteRingBuffer.h"

namespace ke
{
	template<typename T, size_t Size>
	inline RingBuffer<T, Size>::RingBuffer() 
		: _head(0), _tail(0), _count(0) 
	{
	}

	template<typename T, size_t Size>
	inline RingBuffer<T, Size>::~RingBuffer()
	{
		while (_count > 0)
		{
			T* ptr = GET_BUFFER_PTR_AT(T, _buffer, _tail);
			ptr->~T();
			_tail = (_tail + 1) % Size;
			--_count;
		}
	}

	template<typename T, size_t Size>
	inline bool RingBuffer<T, Size>::pushBack(KE_IN const T& item)
	{
		if (_count == Size) return false;

		new (reinterpret_cast<T*>(&_buffer[sizeof(T) * _head])) T(item);

		_head = (_head + 1) % Size;
		++_count;
		return true;
	}

	template<typename T, size_t Size>
	inline bool RingBuffer<T, Size>::pushBack(KE_IN T&& item)
	{
		if (_count == Size) return false;

		new (reinterpret_cast<T*>(&_buffer[sizeof(T) * _head])) T(move(item));

		_head = (_head + 1) % Size;
		++_count;
		return true;
	}

	template<typename T, size_t Size>
	inline bool RingBuffer<T, Size>::popFront(KE_OUT T& item)
	{
		if (_count == 0) return false;

		T* ptr = GET_BUFFER_PTR_AT(T, _buffer, _tail);
		item = *ptr;
		ptr->~T();

		_tail = (_tail + 1) % Size;
		--_count;
		return true;
	}
}