#pragma once
#include "MemoryCommon.h"
#include "MallocAllocator.h"

namespace ke
{
	template<size_t Count, typename T, typename Alloc = MallocAllocator<T>>
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


	private:
		NO_UNIQUE_ADDRESS Alloc		_allocator;
		MemoryEntry					_memoryEntry;

	private:
		void InitializeStorage() noexcept;

	public:
		inline T& operator[](size_t index) { return *(reinterpret_cast<T*>(_memoryEntry._address) + index); }
		inline const T& operator[](size_t index) const { return *(reinterpret_cast<T*>(_memoryEntry._address) + index); }

#ifdef _DEBUG
	private:
		const T* _data = nullptr;
		CONSTEXPR_INLINE static constexpr size_t _count = Count;
#endif
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");
	};
}
#include "StaticArray.hpp"