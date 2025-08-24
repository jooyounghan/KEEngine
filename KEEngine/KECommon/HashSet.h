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
		bool								find(const Key& key);

	public:
		size_t count() const;

		// Static Asserts
		static_assert(KETrait::HashMapBucketTrait<HashBucket, Key, BucketSetUnit>::value, "Bucket does not satisfy the required HashBucketTrait.");
		//static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	};

	template<typename Key, typename HashConvertor>
	using CompactHashSet = HashSet<Key, BinHoodBucketNode<Key, BucketSetUnit, 256>, HashConvertor>;
}

#include "HashSet.hpp"