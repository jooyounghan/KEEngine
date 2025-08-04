#pragma once
#include "MethodTraits.h"
#include "OptionalValue.h"
#include "Iterator.h"

namespace ke
{
	namespace KETrait
	{
#pragma region Iterator Traits
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
#pragma endregion

#pragma region Vector Traits
		DEFINE_METHOD_TRAIT(HasPushBackRValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPushBackLValue, pushBack);
		DEFINE_METHOD_TRAIT(HasPopBack, popBack);

		template<typename Container, typename T>
		struct VectorTrait : TraitCondition<
			SatisfyAll<
			CHECK_METHOD_TRAIT(HasPushBackRValue, Container, void, const T&),
			CHECK_METHOD_TRAIT(HasPushBackLValue, Container, void, T&&),
			CHECK_METHOD_TRAIT(HasPopBack, Container, void)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};
#pragma endregion


#pragma region HashBucket Traits
		DEFINE_METHOD_TRAIT(HasInsertValueWithHash, insert);
		DEFINE_METHOD_TRAIT(HasRemoveHash, remove);
		DEFINE_METHOD_TRAIT_WITH_QUALIFIER(HashFindHash, find, const);

		template<typename HashBucket, typename Value>
		struct HashBucketTrait : TraitCondition<
			SatisfyAll<
			CHECK_METHOD_TRAIT(HasInsertValueWithHash, HashBucket, void, size_t, const Value&),
			CHECK_METHOD_TRAIT(HasRemoveHash, HashBucket, void, size_t),
			CHECK_METHOD_TRAIT(HashFindHash, HashBucket, const OptionalValue<size_t, Value>&, size_t)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};
#pragma endregion
	}
}