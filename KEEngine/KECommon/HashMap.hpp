#pragma once
#include "HashMap.h"
#include "HashConvertor.h"

namespace ke
{
	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::BucketNode(size_t from, size_t to, BucketNode* parent, bool isAllocateValues)
		: _from(from), _to(to), _parent(parent)
	{
		if (isAllocateValues)
			_values = new OptionalValue<size_t, Value>[BucketSize];
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::~BucketNode()
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
	inline bool BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::isInRange(size_t hash) const
	{
		return _from <= hash && hash <= _to;
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	bool BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::hasChildren() const
	{
		return _left != nullptr || _right != nullptr;
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	float BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::getLoadFactor() const
	{
		return static_cast<float>(_count) / static_cast<float>(BucketSize);
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::SplitBucket()
	{
		if (hasChildren()) return;

		size_t mid = (_from + _to) / 2;
		_left = new BucketNode<Value, BucketSize>(_from, mid, this, false);
		_left->_values = _values;
		_left->_count = _count;
		_values = nullptr;

		_right = new BucketNode<Value, BucketSize>(mid + 1, _to, this, true);

		//for (size_t i = 0; i < BucketSize; ++i)
		//{
		//	if (_values[i].hasValue())
		//	{
		//		size_t keyHash = *_values[i].tryGetValue<0>();

		//		if (hash <= mid)
		//		{
		//			_left->_values[i] = move(_values[i]);
		//		}
		//		else
		//		{
		//			_right->_values[i] = move(_values[i]);
		//		}
		//	}
		//}
	}

	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::InsertValue(size_t hash, const Value& value)
	{
	}

	template<typename Key, typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void HashMap<Key, Value, BucketSize, SeperateThreshold, MergeThreshold>::Insert(const Key& key, const Value& value)
	{
	}

	template<typename Key, typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	void HashMap<Key, Value, BucketSize, SeperateThreshold, MergeThreshold>::Remove(const Key& key)
	{
	}

	template<typename Key, typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	const OptionalValue<size_t, Value>& HashMap<Key, Value, BucketSize, SeperateThreshold, MergeThreshold>::Find(const Key& key) const
	{
		// TODO: 여기에 return 문을 삽입합니다.
	}
}