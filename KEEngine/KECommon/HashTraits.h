#pragma once
#include "MethodTraits.h"

namespace ke
{
	namespace KETrait
	{
#pragma region HashBucket Traits
		DEFINE_METHOD_TRAIT(HasInsertValueWithHash, insert);
		DEFINE_METHOD_TRAIT(HasRemoveHash, remove);
		DEFINE_METHOD_TRAIT(HashFindHash, find);

		template<typename HashBucket, typename Key, typename Value>
		struct HashMapBucketTrait : TraitCondition<
			SatisfyAll<
			IsContructible<HashBucket>::value,
			CHECK_METHOD_TRAIT(HasInsertValueWithHash, HashBucket, void, size_t, const Key&, const Value&),
			CHECK_METHOD_TRAIT(HasRemoveHash, HashBucket, void, size_t, const Key&),
			CHECK_METHOD_TRAIT(HashFindHash, HashBucket, bool, size_t, const Key&, Key*&, Value*&)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};

		template<typename HashBucket, typename Key>
		struct HashSetBucketTrait : TraitCondition<
			SatisfyAll<
			IsContructible<HashBucket>::value,
			CHECK_METHOD_TRAIT(HasInsertValueWithHash, HashBucket, void, size_t, const Key&),
			CHECK_METHOD_TRAIT(HasRemoveHash, HashBucket, void, size_t, const Key&),
			CHECK_METHOD_TRAIT(HashFindHash, HashBucket, bool, size_t, const Key&)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};


#pragma endregion

#pragma region HashConvertor Traits
		DEFINE_STATIC_METHOD_TRAIT(HasHashing, operator());

		template<typename HashConvertor, typename Key>
		struct HashConvertorTrait : TraitCondition<
			CHECK_METHOD_TRAIT(HasHashing, HashConvertor, size_t, const Key&), TrueTrait, FalseTrait
		>::Type
		{
		};
#pragma endregion

	}
}