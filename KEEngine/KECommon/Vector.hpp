#pragma once
#include "Vector.h"
#include "ContainerTraits.h"

#include <cstdio>

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
	{
		static_assert(KETrait::VectorTrait<Vector<T, Alloc>, T>::value, "Vector does not satisfy the required traits.");
	}
	template<typename T, typename Alloc>
	Vector<T, Alloc>::~Vector()
	{
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN const T& element)
	{
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN T&& element)
	{
	}

	template<typename T, typename Alloc>
	void Vector<T, Alloc>::popBack(KE_OUT T* elementOut)
	{
		printf("popBack\n");
	}
}