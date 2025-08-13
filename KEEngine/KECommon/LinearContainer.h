#pragma once

namespace ke
{
	template<size_t InitialCount, typename T>
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

	public:
		inline T& operator[](size_t index) { return _data[index]; }
		inline const T& operator[](size_t index) const { return _data[index]; }
	};
}
#include "LinearContainer.hpp"