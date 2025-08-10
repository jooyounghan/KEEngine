#pragma once
#include "StaticArray.h"

namespace ke
{
	template<size_t Count, typename T>
	StaticArray<Count, T>::StaticArray()
	{
	}

	template<size_t Count, typename T>
	template<typename ...Args>
	StaticArray<Count, T>::StaticArray(Args ...args)
	{
	}
}