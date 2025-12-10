#pragma once
#include "HashContainer.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor>
	void HashContainer<Key, Value, BucketSize, HashConvertor>::remove(const Key& key)
	{
		size_t hash = _hashConvertor(key);

		_bucket.remove(hash, key);
	}

	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor>
	HashBucketFindResult<Key, Value> HashContainer<Key, Value, BucketSize, HashConvertor>::find(const Key& key)
	{
		size_t hash = HashContainer<Key, Value, BucketSize, HashConvertor>::_hashConvertor(key);

		HashBucketFindResult<Key, Value> findResult = _bucket.find(hash, key);
		return findResult;
	}

	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor>
	size_t HashContainer<Key, Value, BucketSize, HashConvertor>::count() const
	{
		size_t result = 0;
		_bucket.getTotalSubCount(result);
		return result;
	}

	template<typename Key, typename Value, size_t BucketSize, typename HashConvertor>
	void HashMap<Key, Value, BucketSize, HashConvertor>::insert(const Key& key, const Value& value)
	{
		size_t hash = HashContainer<Key, Value, BucketSize, HashConvertor>::_hashConvertor(key);

		HashBucketInsertEntry<Key, Value> insertEntry(hash, key, value);
		__super::_bucket.insert(insertEntry);
	}

	template<typename Key, size_t BucketSize, typename HashConvertor>
	void HashSet<Key, BucketSize, HashConvertor>::insert(const Key& key)
	{
		size_t hash = HashContainer<Key, void, BucketSize, HashConvertor>::_hashConvertor(key);

		HashBucketInsertEntry<Key> insertEntry(hash, key);
		__super::_bucket.insert(insertEntry);
	}
}