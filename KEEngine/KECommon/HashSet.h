#pragma once
#include "BinHoodBucketNode.h"
#include "HashGenerator.h"

namespace ke
{
	struct BucketSetUnit
	{
		BucketSetUnit() {}
		BucketSetUnit(const BucketSetUnit&) {}
		BucketSetUnit(BucketSetUnit&&) {}
		BucketSetUnit& operator=(const BucketSetUnit&) { return *this; }
		BucketSetUnit& operator=(BucketSetUnit&&) { return *this; }
		~BucketSetUnit() {}
	};


	template<typename Key, typename HashBucket = BinHoodBucketNode<Key, BucketSetUnit, 256>, typename HashConvertor = HashGenerator<Key>>
	class HashSet
	{
	public:
		~HashSet();

	private:
		HashBucket* _bucket = new HashBucket();
		NO_UNIQUE_ADDRESS HashConvertor _hashConvertor;

	public:
		void								insert(const Key& key);
		void								remove(const Key& key);
		Key*								find(const Key& key);

	public:
		size_t count() const;

		// Static Asserts
		static_assert(KETrait::HashMapBucketTrait<HashBucket, Key, BucketSetUnit>::value, "Bucket does not satisfy the required HashBucketTrait.");
		static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	};

	template<typename Key, typename HashConvertor>
	using CompactBinHoodHashSet = HashSet<Key, BinHoodBucketNode<Key, BucketSetUnit, 64>, HashConvertor>;
	template<typename Key, typename HashConvertor>
	using StandardBinHoodHashSet = HashSet<Key, BinHoodBucketNode<Key, BucketSetUnit, 256>, HashConvertor>;
	template<typename Key, typename HashConvertor>
	using LargeBinHoodHashSet = HashSet<Key, BinHoodBucketNode<Key, BucketSetUnit, 1024>, HashConvertor>;
	template<typename Key, size_t BucketSize, typename HashConvertor>
	using MaxBinHoodHashSet = HashSet<Key, BinHoodBucketNode<Key, BucketSetUnit, KEMath::getNextPowerOf2(BucketSize)>, HashConvertor>;
}

#include "HashSet.hpp"