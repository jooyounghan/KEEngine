#pragma once
#include "TypeTraits.h"

namespace ke
{
	namespace KETrait
	{
        template<typename Container, typename T>
        struct VectorTrait
        {
			//static constexpr bool value = SatisfyAll<
			//	IsClass<Container>::value,
			//	HasMethod<Container, void, KE_IN const T&>::value,
			//	HasMethod<Container, void, KE_IN T&&>::value,
			//	HasMethod<Container, void, KE_IN T*>::value
			//>::value;
        };
	};
}