#pragma once
#include "MethodTraits.h"
#include "Iterator.h"

namespace ke
{
	namespace KETrait
	{
		DEFINE_METHOD_TRAIT(HasBegin, begin);
		DEFINE_METHOD_TRAIT(HasEnd, end);
		DEFINE_METHOD_TRAIT_WITH_QUALIFIER(HasConstBegin, begin, const);
		DEFINE_METHOD_TRAIT_WITH_QUALIFIER(HasConstEnd, end, const);

		template<typename Container, typename T>
		struct IterableTrait : TraitCondition<
			SatisfyAll<
			CHECK_METHOD_TRAIT(HasBegin, Container, Iterator<T>),
			CHECK_METHOD_TRAIT(HasEnd, Container, Iterator<T>),
			CHECK_METHOD_TRAIT(HasConstBegin, Container, const ConstIterator<T>),
			CHECK_METHOD_TRAIT(HasConstEnd, Container, const ConstIterator<T>)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};


		DEFINE_METHOD_TRAIT(HasPushBackRValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPushBackLValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPopBack, popBack);

		template<typename Container, typename T>
		struct VectorTrait : TraitCondition<
			SatisfyAll<
			CHECK_METHOD_TRAIT(HasPushBackRValue, Container, void, const T&),
			CHECK_METHOD_TRAIT(HasPushBackLValue, Container, void, T&&),
			CHECK_METHOD_TRAIT(HasPopBack, Container, void, T*)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};
	}
}