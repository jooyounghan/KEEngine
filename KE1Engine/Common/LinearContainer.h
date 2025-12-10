#pragma once

namespace ke
{
	template<typename T, size_t InitialCount = 0>
	class LinearContainer
	{
	public:
		LinearContainer();
		LinearContainer(const LinearContainer&);
		LinearContainer(LinearContainer&&) noexcept;
		LinearContainer& operator=(const LinearContainer&);
		LinearContainer& operator=(LinearContainer&&) noexcept;

	public:
		virtual ~LinearContainer();

	protected:
		T* _data = nullptr;
		size_t _count = InitialCount;

	protected:
		void release();

	public:
		inline size_t size() const { return _count; }
		inline T& operator[](size_t index) { return _data[index]; }
		inline const T& operator[](size_t index) const { return _data[index]; }
		inline const T* data() const { return _data; }
		inline T*		data() { return _data; }

	public:
		inline void swap(size_t idx1, size_t idx2);
		inline void swap(size_t idx, T& target);
	};
}
#include "LinearContainer.hpp"