#pragma once
#include "StaticArray.h"

namespace ke
{
	template<typename T, size_t Count>
	template<typename ...Args>
	StaticArray<T, Count>::StaticArray(Args ...args)
		: LinearContainer<T, Count>()
	{
		for (size_t idx = 0; idx < Count; ++idx)
		{
			new (__super::_data + idx) T(args...);
		}
	}
}