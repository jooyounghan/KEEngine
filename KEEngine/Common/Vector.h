#pragma once
#include "LinearContainer.h"
#include "ContainerTraits.h"

namespace ke
{
	template<typename T>
	class Vector : public LinearContainer<T>
	{
	public:
		Vector() = default;
		Vector(const Vector& other) = default;
		Vector(Vector&& other) noexcept = default;

	public:
		~Vector() = default;

	public:
		Vector& operator=(const Vector& other) = default;
		Vector& operator=(Vector&& other) noexcept = default;

	public:
		inline size_t capacity() const { return _capacity; }

	public:
		void pushBack(const T& element);
		void pushBack(T&& element);

	private:
		template<typename U>
		void pushBackImpl(U&& element);

	public:
		void popBack();

	public:
		template<typename... Args>
		void resize(size_t newSize, Args&&... args);
		void reserve(size_t newCapacity);

	private:
		void reallocateCapcity(size_t newCapacity);
		void decreaseCount(size_t newCount);

	private:
		size_t _capacity = 0;

		// Static Asserts
		static_assert(KETrait::VectorTrait<Vector, T>::value, "Vector does not satisfy the required VectorTrait.");
	};
}

#include "Vector.hpp"
