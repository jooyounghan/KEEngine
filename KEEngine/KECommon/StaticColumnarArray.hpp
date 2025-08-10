#pragma once
#include "StaticColumnarArray.h"

namespace ke
{
	template<size_t Count, typename ...Ts>
	StaticColumnarArray<Count, Ts...>::StaticColumnarArray()
	{
	}
	
	template<size_t Count, typename ...Ts>
	template<typename ...Args>
	StaticColumnarArray<Count, Ts...>::StaticColumnarArray(Args ...args)
	{
	}
}