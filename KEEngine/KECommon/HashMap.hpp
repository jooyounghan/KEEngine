#pragma once
#include "HashMap.h"
#include "HashConvertor.h"

namespace ke
{
	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::BinHoodBucketNode()
		: _from(0), _to(KELimit::getMax<size_t>()), _parent(nullptr)
	{
		_values = new OptionalValue<HashValue, Value, SlotDistance>[BucketSize];
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent, bool isAllocateValues)
		: _from(from), _to(to), _parent(parent)
	{
		if (isAllocateValues)
			_values = new OptionalValue<HashValue, Value, SlotDistance>[BucketSize];
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::~BinHoodBucketNode()
	{
		if (_left != nullptr)
		{
			delete _left;
			_left = nullptr;
		}

		if (_right != nullptr)
		{
			delete _right;
			_right = nullptr;
		}

		if (_values != nullptr)
		{
			delete _values;
			_values = nullptr;
		}
	}
	
	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	inline bool BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::isInRange(HashValue hash) const
	{
		return _from <= hash && hash <= _to;
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	bool BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::hasChildren() const
	{
		return _left != nullptr || _right != nullptr;
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	float BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::getLoadFactor() const
	{
		return static_cast<float>(_count) / static_cast<float>(BucketSize);
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::splitBucket()
	{
		if (hasChildren()) return;

		HashValue mid = (_from + _to) / 2;

		// left node dosen't initialize slots but moved from parent
		_left = new BinHoodBucketNode(_from, mid, this, false);
		_left->_values = _values;
		_left->_count = _count;
		
		_count = 0;
		_values = nullptr;

		// right node initialize slots
		_right = new BinHoodBucketNode(mid + 1, _to, this, true);

		for (size_t i = 0; i < BucketSize; ++i)
		{
			OptionalValue<HashValue, Value, SlotDistance>& currentOptionalValue = _left->_values[i];
			if (currentOptionalValue.hasValue())
			{
				const HashValue&	hashValue = *currentOptionalValue.tryGetValue<0>();
				const Value&		value = *currentOptionalValue.tryGetValue<1>();

				if (_right->isInRange(hashValue))
				{
					_right->insert(hashValue, value);
					
					_left->remove(hashValue);
					// 임시
					currentOptionalValue.~OptionalValue();
					_left->_count--;
				}
			}
		}
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::insert(HashValue hash, const Value& value)
	{
		if (hasChildren())
		{
			if (_left->isInRange(hash))
			{
				_left->insert(hash, value);
				return;
			}
			else
			{
				_right->insert(hash, value);
				return;
			}
		}

		size_t idx = hash % BucketSize;
		OptionalValue<HashValue, Value, SlotDistance> incoming(hash, value, 0);

		while (true) 
		{
			if (!_values[idx].hasValue())
 {
				_values[idx] = incoming;
				++_count;
				break;
			}

			uint32 currentHash = *(_values[idx].tryGetValue<0>());
			if (currentHash == hash)
			{
				_values[idx].setValue<1>(value);
				break;
			}

			uint32 currentDistance = *(_values[idx].tryGetValue<2>());
			uint32 incomingDistance = *(incoming.tryGetValue<2>());
			if (currentDistance < incomingDistance)
			{
				OptionalValue<HashValue, Value, SlotDistance> temp = move(_values[idx]);
				_values[idx] = incoming;
				incoming = move(temp);
			}

			idx = (idx + 1) % BucketSize;
			incoming.setValue<2>(*incoming.tryGetValue<2>() + 1);
		}

		if (getLoadFactor() > SeperateThreshold)
		{
			splitBucket();
		}
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::remove(HashValue hash)
	{
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	const OptionalValue<size_t, Value>& BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::find(HashValue hash) const
	{
		// TODO: 여기에 return 문을 삽입합니다.
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::getCount(size_t& sizeOut) const
	{
		sizeOut += _count;
		if (hasChildren())
		{
			_left->getCount(sizeOut);
			_right->getCount(sizeOut);
		}
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	void HashMap<Key, Value, Bucket, HashConvertor>::insert(const Key& key, const Value& value)
	{
		size_t hash = _hashConvertor.convertToHash(key);
		_bucket->insert(hash, value);
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	void HashMap<Key, Value, Bucket, HashConvertor>::remove(const Key& key)
	{
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	const OptionalValue<size_t, Value>& HashMap<Key, Value, Bucket, HashConvertor>::find(const Key& key) const
	{
	}
	
	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	size_t HashMap<Key, Value, HashBucket, HashConvertor>::getCount() const 
	{ 
		size_t result = 0; 
		_bucket->getCount(result); 
		return result; 
	}
}