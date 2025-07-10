#pragma once
#include "TypeTraits.h"

namespace ke
{
	namespace KETrait
	{
		template<typename Container, typename T>
		struct VectorTrait
		{
			DEFINE_HAS_METHOD(pushBackRValue, pushBack, DEFINE_METHOD_POINTER(Container, void, KE_IN const T&));
			DEFINE_HAS_METHOD(pushBackLValue, pushBack, DEFINE_METHOD_POINTER(Container, void, KE_IN T&&));
			DEFINE_HAS_METHOD(popBack, popBack, DEFINE_METHOD_POINTER(Container, void, KE_OUT T*));

			static constexpr bool value = SatisfyAll<
				CHECK_HAS_METHOD(pushBackRValue, Container),
				CHECK_HAS_METHOD(pushBackLValue, Container),
				CHECK_HAS_METHOD(popBack, Container)
			>::value;
		};
	};
}