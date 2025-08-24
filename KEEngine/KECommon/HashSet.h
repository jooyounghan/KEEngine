#pragma once
#include "BinHoodBucketNode.h"
#include "HashGenerator.h"

namespace ke
{
	//template<typename Key, typename HashBucket = BinHoodBucketNode<Key, void, 64>, typename HashConvertor = HashGenerator<Key>>
	//class HashSet
	//{
	//public:
	//	~HashSet();

	//private:
	//	HashBucket* _bucket = new HashBucket();
	//	NO_UNIQUE_ADDRESS HashConvertor _hashConvertor;

	//public:
	//	void								insert(const Key& key);
	//	void								remove(const Key& key);
	//	bool								find(const Key& key) const;

	//public:
	//	size_t count() const;

	//	// Static Asserts
	//	static_assert(KETrait::HashBucketTrait<HashBucket, Key, void>::value, "Bucket does not satisfy the required HashBucketTrait.");
	//	//static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	//};

	//template<typename Key, typename HashConvertor>
	//using CompactHashSet = HashSet<Key, BinHoodBucketNode<Key, void, 256>, HashConvertor>;
}

#include "HashSet.hpp"