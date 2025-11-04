#pragma once
#include "BinHoodBucketNode.h"
#include "HashGenerator.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor = HashGenerator<Key>>
	class HashContainer
	{
	public:
		HashContainer() = default;
		~HashContainer() = default;

	protected:
		BinHoodBucketNode<Key, Value, KEMath::getNextPowerOf2(BucketSize)>	_bucket;
		static HashConvertor												_hashConvertor;

	public:
		void								remove(const Key& key);
		HashBucketFindResult<Key, Value>	find(const Key& key);
		size_t								count() const;

		// Static Asserts
		static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	};


	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor = HashGenerator<Key>>
	class HashMap : public HashContainer<Key, Value, BucketSize, HashConvertor>
	{
	public:
		HashMap() = default;
		~HashMap() = default;

	public:
		void insert(const Key& key, const Value& value);
	};

	template<typename Key, typename Value, typename HashConvertor = HashGenerator<Key>>
	using CompactBinHoodHashMap = HashMap<Key, Value, 64, HashConvertor>;
	template<typename Key, typename Value, typename HashConvertor = HashGenerator<Key>>
	using LargeBinHoodHashMap = HashMap<Key, Value, 1024, HashConvertor>;

	template<typename Key, size_t BucketSize, typename HashConvertor = HashGenerator<Key>>
	class HashSet : public HashContainer<Key, void, BucketSize, HashConvertor>
	{
	public:
		HashSet() = default;
		~HashSet() = default;

	public:
		void insert(const Key& key);
	};
}

#include "HashContainer.hpp"