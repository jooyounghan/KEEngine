#pragma once
#include "Vector.h"
#include "ContainerTrait.h"

#include <cstdio>

namespace ke
{
	template<typename T, typename Alloc>
	Vector<T, Alloc>::Vector()
	{
		static_assert(KETrait::VectorTrait<Vector<T, Alloc>, T>::value, "Vector must implement methods declared in struct VectorTrait.");

		// This Has Compile Error
		//printf("pushBackRValue trait: %d\n", KETrait::pushBackRValue<Vector<T, Alloc>>::value);
		//printf("pushBackLValue trait: %d\n", KETrait::pushBackLValue<Vector<T, Alloc>>::value);
		//printf("popBack trait: %d\n", KETrait::popBack<Vector<T, Alloc>>::value);
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