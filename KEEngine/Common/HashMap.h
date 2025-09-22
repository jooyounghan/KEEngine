#pragma once
#include "BinHoodBucketNode.h"
#include "HashGenerator.h"

namespace ke
{
	template<typename Key, typename Value, typename HashBucket = BinHoodBucketNode<Key, Value, 256>, typename HashConvertor = HashGenerator<Key>>
	class HashMap
	{
	public:
		~HashMap();

	private:
		HashBucket* _bucket = new HashBucket();
		static HashConvertor _hashConvertor;

	public:
		void								insert(const Key& key, const Value& value);
		void								remove(const Key& key);
		Value*								find(const Key& key);

	public:
		size_t count() const;

		// Static Asserts
		static_assert(KETrait::HashMapBucketTrait<HashBucket, Key, Value>::value, "Bucket does not satisfy the required HashBucketTrait.");
		//static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	};

	template<typename Key, typename Value, typename HashConvertor = HashGenerator<Key>>
	using CompactBinHoodHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, 64>, HashConvertor>;
	template<typename Key, typename Value, typename HashConvertor = HashGenerator<Key>>
	using StandardBinHoodHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, 256>, HashConvertor>;
	template<typename Key, typename Value, typename HashConvertor = HashGenerator<Key>>
	using LargeBinHoodHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, 1024>, HashConvertor>;
	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor = HashGenerator<Key>>
	using MaxBinHoodHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, KEMath::getNextPowerOf2(BucketSize)>, HashConvertor>;
}

#include "HashMap.hpp"