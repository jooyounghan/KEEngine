#pragma once
#include "HashMap.h"
#include "HashSet.h"

namespace ke
{
	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	HashMap<Key, Value, HashBucket, HashConvertor>::~HashMap()
	{
		if (_bucket)
		{
			delete _bucket;
			_bucket = nullptr;
		}
	}

	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	void HashMap<Key, Value, HashBucket, HashConvertor>::insert(const Key& key, const Value& value)
	{
		size_t hash = _hashConvertor(key);
		_bucket->insert(hash, key, value);
	}

	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	void HashMap<Key, Value, HashBucket, HashConvertor>::remove(const Key& key)
	{
		size_t hash = _hashConvertor(key);
		_bucket->remove(hash, key);
	}

	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	const Value* HashMap<Key, Value, HashBucket, HashConvertor>::find(const Key& key) const
	{
		size_t hash = _hashConvertor(key);
		return _bucket->find(hash, key);
	}
	
	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	size_t HashMap<Key, Value, HashBucket, HashConvertor>::count() const
	{ 
		size_t result = 0; 
		_bucket->count(result); 
		return result; 
	}
}