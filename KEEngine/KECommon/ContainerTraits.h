#pragma once
#include "MethodTraits.h"

namespace ke
{
	namespace KETrait
	{
		DEFINE_METHOD_TRAIT(HasPushBackRValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPushBackLValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPopBack, popBack);

        template<typename Container, typename T>
        struct VectorTrait : TraitCondition<
			SatisfyAll<
				CHECK_METHOD_TRAIT(HasPushBackRValue, Container, void, const T&),
				CHECK_METHOD_TRAIT(HasPushBackLValue, Container, void, T&&),
				CHECK_METHOD_TRAIT(HasPopBack, Container, void, T*)
			>::value, TrueTrait, FalseTrait>::Type
        {
        };




	};
}