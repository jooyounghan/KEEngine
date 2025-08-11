#pragma once
#include "MallocAllocator.h"
#include "ContainerTraits.h"

namespace ke
{
	template<typename T, typename Alloc = MallocAllocator<T>>
	class Vector
	{
	public:
		Vector();
		Vector(const Vector&);
		Vector(Vector&&) noexcept;

	public:
		Vector& operator=(const Vector&);
		Vector& operator=(Vector&&) noexcept;

	public:
		~Vector();

	private:
		NO_UNIQUE_ADDRESS Alloc		_allocator;
		MemoryEntry					_memoryEntry;
		size_t						_count;

	public:
		inline size_t size() const;
		inline size_t capacity() const;

	public:
		void pushBack(KE_IN const T& element);
		void pushBack(KE_IN T&& element);

	private:
		template<typename U>
		void pushBackImpl(KE_IN U&& element);

	public:
		void popBack();

	public:
		template<typename... Args>
		void resize(size_t newSize, Args&&... args);
		void reserve(size_t newCapacity);

	public:
		inline T& operator[](size_t index) { return *(reinterpret_cast<T*>(&_memoryEntry._address[0]) + index); }
		inline const T& operator[](size_t index) const { return *(reinterpret_cast<T*>(&_memoryEntry._address[0]) + index); }

	private:
		void reallocateCapcity(size_t newCapacity);
		void decreaseCount(size_t newCount);

#ifdef _DEBUG
	private:
		const T* _data = nullptr;
#endif

		// Static Asserts
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");
		static_assert(KETrait::VectorTrait<Vector, T>::value, "Vector does not satisfy the required VectorTrait.");
	};
}

#include "Vector.hpp"
