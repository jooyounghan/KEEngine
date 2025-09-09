#pragma once
#include "LinearContainer.h"
#include "MallocAllocator.h"

namespace ke
{
	template<typename T, size_t Count>
	class StaticArray : public LinearContainer<T, Count>
	{
	public:
		StaticArray();
		template<typename... Args>
		StaticArray(Args... args);
		StaticArray(const StaticArray& other) = default;
		StaticArray(StaticArray&& other) noexcept = default;

	public:
		~StaticArray() = default;
		
	public:
		StaticArray& operator=(const StaticArray& other) = default;
		StaticArray& operator=(StaticArray&& other) noexcept = default;
	};
}
#include "StaticArray.hpp"