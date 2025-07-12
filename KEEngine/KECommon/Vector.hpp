#pragma once
#include "Vector.h"
#include "ContainerTrait.h"

#include <cstdio>

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
	{
		
	}
	template<typename T, typename Alloc>
	Vector<T, Alloc>::~Vector()
	{
	}
	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN const T& element)
	{
		printf("pushBack const T&\n");
	}
	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pushBack(KE_IN T&& element)
	{
		printf("pushBack T&&\n");
	}
	template<typename T, typename Alloc>
	void Vector<T, Alloc>::popBack(KE_OUT T* elementOut)
	{
		printf("popBack\n");
	}
}