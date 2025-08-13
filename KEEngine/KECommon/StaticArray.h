#pragma once
#include "MemoryCommon.h"
#include "MallocAllocator.h"

namespace ke
{
	template<size_t Count, typename T>
	class StaticArray
	{
	public:
		StaticArray();
		template<typename... Args>
		StaticArray(Args... args);
		StaticArray(const StaticArray& other);
		StaticArray(StaticArray&& other) noexcept;

	public:
		~StaticArray();
		
	public:
		StaticArray& operator=(const StaticArray& other);
		StaticArray& operator=(StaticArray&& other) noexcept;

	public:
		inline T& operator[](size_t index) { return _data[index]; }
		inline const T& operator[](size_t index) const { return _data[index]; }

	private:
		T* _data = nullptr;

#ifdef _DEBUG
	private:
		CONSTEXPR_INLINE static constexpr size_t _count = Count;
#endif
	};
}
#include "StaticArray.hpp"