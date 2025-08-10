#pragma once
#include "MemoryCommon.h"

namespace ke
{
	template<size_t Count, typename T>
	class StaticArray
	{
	public:
		StaticArray();
		template<typename... Args>
		StaticArray(Args... args);
		~StaticArray() = default;

	private:
		alignas(T) byte _storage[KEMemory::getPaddedSizeOf<T>() * Count];

	public:
		inline T& operator[](size_t index) { return *(reinterpret_cast<T*>(&_storage[0]) + index); }
		inline const T& operator[](size_t index) const { return *(reinterpret_cast<T*>(&_storage[0]) + index); }

#ifdef _DEBUG
	private:
		const T* _data = reinterpret_cast<T*>(&_storage[0]);
#endif

	};
}
#include "StaticArray.hpp"