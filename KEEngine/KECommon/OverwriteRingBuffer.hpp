#pragma once
#include "OverwriteRingBuffer.h"

namespace ke
{
	template<typename T, size_t Size>
	inline OverwriteRingBuffer<T, Size>::OverwriteRingBuffer()
		: _head(0), _tail(0), _count(0)
	{
	}

	template<typename T, size_t Size>
	inline OverwriteRingBuffer<T, Size>::~OverwriteRingBuffer()
	{
		while (_count > 0)
		{
			T* ptr = reinterpret_cast<T*>(&_buffer[sizeof(T) * _tail]);
			ptr->~T();
			_tail = (_tail + 1) % Size;
			--_count;
		}
	}

	template<typename T, size_t Size>
	inline bool OverwriteRingBuffer<T, Size>::pushBack(KE_IN const T& item)
	{
		if (isFull())
		{
			T* old = GET_BUFFER_PTR_AT(T, _buffer, _tail);
			old->~T();
			_tail = (_tail + 1) % Size;
			--_count;
		}

		new (GET_BUFFER_PTR_AT(T, _buffer, _head)) T(item);
		_head = (_head + 1) % Size;
		++_count;
		return true;
	}

	template<typename T, size_t Size>
	inline bool OverwriteRingBuffer<T, Size>::pushBack(KE_IN T&& item)
	{
		if (isFull())
		{
			T* old = GET_BUFFER_PTR_AT(T, _buffer, _tail);
			old->~T();
			_tail = (_tail + 1) % Size;
			--_count;
		}

		new (GET_BUFFER_PTR_AT(T, _buffer, _head)) T(move(item));
		_head = (_head + 1) % Size;
		++_count;
		return true;
	}

	template<typename T, size_t Size>
	inline bool OverwriteRingBuffer<T, Size>::popFront(KE_OUT T& item)
	{
		if (_count == 0) return false;

		T* ptr = reinterpret_cast<T*>(&_buffer[sizeof(T) * _tail]);
		item = *ptr;
		ptr->~T();

		_tail = (_tail + 1) % Size;
		--_count;
		return true;
	}
}