#pragma once
#include "BinHoodBucketNode.h"
#include "HashGenerator.h"

namespace ke
{
	template<typename Key, typename Value, typename HashBucket = BinHoodBucketNode<Key, Value, 64>, typename HashConvertor = HashGenerator<Key>>
	class HashMap
	{
	public:
		~HashMap();

	private:
		HashBucket* _bucket = new HashBucket();
		NO_UNIQUE_ADDRESS HashConvertor _hashConvertor;

	public:
		void								insert(const Key& key, const Value& value);
		void								remove(const Key& key);
		const Value*						find(const Key& key) const;

	public:
		size_t count() const;

		// Static Asserts
		static_assert(KETrait::HashBucketTrait<HashBucket, Key, Value>::value, "Bucket does not satisfy the required HashBucketTrait.");
		//static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
	};

	template<typename Key, typename Value, typename HashConvertor>
	using CompactHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, 256>, HashConvertor>;
}

#include "HashMap.hpp"