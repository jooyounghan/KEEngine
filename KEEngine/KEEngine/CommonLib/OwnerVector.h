#pragma once

namespace ke
{
	template<typename T>
	class OwnerVector
	{
	public:
		OwnerVector() = default;
		~OwnerVector();
		OwnerVector(const OwnerVector&) = delete;
		OwnerVector(OwnerVector&& ownerVector);

	public:
		OwnerVector<T>& operator=(const OwnerVector&) = delete;
		OwnerVector<T>& operator=(OwnerVector&& ownerVector);

	private:
		void move(OwnerVector&& ownerVector);

	public:
		inline const T* operator[](const size_t idx) const { return _pointer[idx]; }
		inline T* operator[](const size_t idx) { return _pointer[idx]; };

	private:
		T**		_pointer = nullptr;
		size_t	_count = 0;
		size_t	_capacity = 0;

	private:
		static size_t calculateTargetCapacity(const size_t targetCount, const size_t currentCapacity);

	private:
		void reallocateCapacity(size_t newCapacity);

	public:
		inline const T** data() const { return _pointer; }
		inline const size_t size() const { return _count; }

	public:
		void swap(const size_t idx1, const size_t idx2);

	public:
		template<typename U = T, typename ...Args>
		T* push_back(Args... args);
		T* push_back(T* ptr);
		void pop_back();

	public:
		template<typename ...Args>
		void insert(const size_t idx, bool preserveOrder, Args... args);
		void erase(const size_t idx, bool preserveOrder = true);

	public:
		inline T** begin() { return _pointer; }
		inline T** end() { return _pointer + _count; }
		inline const T** begin() const { return const_cast<const T**>(_pointer); }
		inline const T** end() const { return const_cast<const T**>(_pointer + _count); }


	private:
		inline void clearPointerContainerXXX() { delete[] _pointer; }

	public:
		void reset();
	};

}
#include "OwnerVector.hpp"