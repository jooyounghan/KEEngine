#pragma once
#include "HashSet.h"

namespace ke
{
	template<typename Key, typename HashBucket, typename HashConvertor>
	inline HashSet<Key, HashBucket, HashConvertor>::~HashSet()
	{
		KEMemory::SafeRelease(_bucket);
	}

	template<typename Key, typename HashBucket, typename HashConvertor>
	inline void HashSet<Key, HashBucket, HashConvertor>::insert(const Key& key)
	{
		size_t hash = _hashConvertor(key);
		_bucket->insert(hash, key, BucketSetUnit());
	}

	template<typename Key, typename HashBucket, typename HashConvertor>
	void HashSet<Key, HashBucket, HashConvertor>::remove(const Key& key)
	{
		size_t hash = _hashConvertor(key);
		_bucket->remove(hash, key);
	}

	template<typename Key, typename HashBucket, typename HashConvertor>
	Key* HashSet<Key, HashBucket, HashConvertor>::find(const Key& key)
	{
		size_t hash = _hashConvertor(key);
		Key* foundKey = nullptr;
		BucketSetUnit* foundValue = nullptr;
		_bucket->find(hash, key, foundKey, foundValue);
		return foundKey;
	}

	template<typename Key, typename HashBucket, typename HashConvertor>
	size_t HashSet<Key, HashBucket, HashConvertor>::count() const
	{
		size_t result = 0;
		_bucket->count(result);
		return result;
	}
}