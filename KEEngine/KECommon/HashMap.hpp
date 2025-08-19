#pragma once
#include "HashMap.h"
#include "HashGenerator.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode()
		: _from(0), _to(KELimit::getMax<HashValue>())
	{
		_values = new StaticColumnarArray<BucketSize, IsOccupied, HashValue, Key, Value, SlotDistance>();
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent, bool isAllocateValues)
		: _from(from), _to(to), _parent(parent)
	{
		if (isAllocateValues)
			_values = new StaticColumnarArray<BucketSize, IsOccupied, HashValue, Key, Value, SlotDistance>();
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::~BinHoodBucketNode()
	{
		KEMemory::SafeRelease(_left);
		KEMemory::SafeRelease(_right);
		KEMemory::SafeRelease(_values);
	}
	
	template<typename Key, typename Value, size_t BucketSize>
	inline bool BinHoodBucketNode<Key, Value, BucketSize>::isInRange(HashValue hash) const
	{
		return _from <= hash && hash <= _to;
	}

	template<typename Key, typename Value, size_t BucketSize>
	bool BinHoodBucketNode<Key, Value, BucketSize>::hasChildren() const
	{
		return _left != nullptr || _right != nullptr;
	}

	template<typename Key, typename Value, size_t BucketSize>
	float BinHoodBucketNode<Key, Value, BucketSize>::getLoadFactor() const
	{
		return static_cast<float>(_count) / static_cast<float>(BucketSize);
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::splitBucket()
	{
		if (hasChildren()) return;

		HashValue mid = _from + (_to - _from) / 2;

		// left node dosen't initialize slots but moved from parent
		_left = new BinHoodBucketNode(_from, mid, this, false);
		_left->_count = _count;
		_count = 0;
		_left->_values = _values;		
		_values = nullptr;

		// right node initialize slots
		_right = new BinHoodBucketNode(mid + 1, _to, this, true);

		for (size_t i = 0; i < BucketSize; ++i)
		{
			if (_left->getIsOccupied(i))
			{
				HashValue hashValue = _left->getHashValue(i);
				Key& key = *_left->getKeyPtr(i);
				Value& value = *_left->getValuePtr(i);
			
				if (_right->isInRange(hashValue))
				{
					_right->insert(hashValue, key, value);
					_left->remove(hashValue, key);
				}
			}
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::shiftBack(size_t currentIdx)
	{
		while (true) 
		{
			int nextIdx = (currentIdx + 1) % BucketSize;

			IsOccupied& nextIsOccupied = getIsOccupied(nextIdx);
			const SlotDistance& nextSlotDistance = getSlotDistance(nextIdx);

			if (!nextIsOccupied || nextSlotDistance == 0) break;

			setHashSlot(currentIdx, nextIsOccupied, getHashValue(nextIdx), move(*getKeyPtr(nextIdx)), move(*getValuePtr(nextIdx)), nextSlotDistance - 1);
			nextIsOccupied = false;

			currentIdx = nextIdx;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::insert(HashValue hash, const Key& key, const Value& value)
	{
		if (hasChildren())
		{
			if (_left->isInRange(hash))
			{
				_left->insert(hash, key, value);
				return;
			}
			else
			{
				_right->insert(hash, key, value);
				return;
			}
		}

		size_t idx = hash % BucketSize;

		bool targetIsOccupied = true;
		HashValue targetHash = hash;
		Key targetKey = key;
		Value targetValue = value;
		SlotDistance targetSlotDistance = 0;

		while (true) 
		{
			bool& isCurrentOccupied = getIsOccupied(idx);
			if (isCurrentOccupied == false)
			{
				setHashSlot(idx, targetIsOccupied, targetHash, move(targetKey), move(targetValue), targetSlotDistance);
				++_count;
				break;
			}

			Key& currentKey = *getKeyPtr(idx);

			if (currentKey == key)
			{
				setHashSlot(idx, move(value));
				break;
			}

			SlotDistance currentDistance = getSlotDistance(idx);
			if (currentDistance < targetSlotDistance)
			{
				swapHashSlot(idx, targetIsOccupied, targetHash, targetKey, targetValue, targetSlotDistance);
			}

			idx = (idx + 1) % BucketSize;
			++targetSlotDistance;
		}

		if (getLoadFactor() > SeperateThreshold)
		{
			splitBucket();
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::remove(HashValue hash, const Key& key)
	{
		size_t idx = hash % BucketSize;
		SlotDistance slotDistance = 0;

		while (true)
		{
			bool& isOccupied = getIsOccupied(idx);
			if (!isOccupied)
				return;

			Key& currentKey = *getKeyPtr(idx);
			if (currentKey == key)
			{
				Value& currentValue = *getValuePtr(idx);
				
				isOccupied = false;
				currentKey.~Key();
				currentValue.~Value();

				shiftBack(idx);
				--_count;
				return;
			}

			SlotDistance& currentSlotDistance = getSlotDistance(idx);
			if (currentSlotDistance < slotDistance)
				return;

			idx = (idx + 1) % BucketSize;
			++slotDistance;
		}
	}

#pragma region Helper
	template<typename Key, typename Value, size_t BucketSize>
	bool& BinHoodBucketNode<Key, Value, BucketSize>::getIsOccupied(size_t idx) const
	{
		return _values->getElement<0>(idx);
	}

	template<typename Key, typename Value, size_t BucketSize>
	inline BinHoodBucketNode<Key, Value, BucketSize>::HashValue& BinHoodBucketNode<Key, Value, BucketSize>::getHashValue(size_t idx) const
	{
		return _values->getElement<1>(idx);
	}

	template<typename Key, typename Value, size_t BucketSize>
	Key* BinHoodBucketNode<Key, Value, BucketSize>::getKeyPtr(size_t idx)
	{
		return &_values->getElement<2>(idx);
	}

	template<typename Key, typename Value, size_t BucketSize>
	Value* BinHoodBucketNode<Key, Value, BucketSize>::getValuePtr(size_t idx)
	{
		return &_values->getElement<3>(idx);
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::SlotDistance& BinHoodBucketNode<Key, Value, BucketSize>::getSlotDistance(size_t idx) const
	{
		return _values->getColumn<4>()[idx];
	}

	template<typename Key, typename Value, size_t BucketSize>
	inline void BinHoodBucketNode<Key, Value, BucketSize>::setHashSlot(size_t idx, const Value& value)
	{
		getIsOccupied(idx) = true;
		new(getValuePtr(idx)) Value(value);
	}

	template<typename Key, typename Value, size_t BucketSize>
	inline void BinHoodBucketNode<Key, Value, BucketSize>::setHashSlot(size_t idx, Value&& value)
	{
		getIsOccupied(idx) = true;
		new(getValuePtr(idx)) Value(move(value));
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::setHashSlot(size_t idx, bool isOccupied, HashValue hashValue, const Key& key, const Value& value, SlotDistance distance)
	{
		getIsOccupied(idx) = isOccupied;
		getHashValue(idx) = hashValue;
		new(getKeyPtr(idx)) Key(key);
		new(getValuePtr(idx)) Value(value);
		getSlotDistance(idx) = distance;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::setHashSlot(size_t idx, bool isOccupied, HashValue hashValue, Key&& key, Value&& value, SlotDistance distance)
	{
		getIsOccupied(idx) = isOccupied;
		getHashValue(idx) = hashValue;
		new(getKeyPtr(idx)) Key(move(key));
		new(getValuePtr(idx)) Value(move(value));
		getSlotDistance(idx) = distance;
	}

	template<typename Key, typename Value, size_t BucketSize>
	inline void BinHoodBucketNode<Key, Value, BucketSize>::swapHashSlot(size_t idx, bool& isOccupied, HashValue& hashValue, Key& key, Value& value, SlotDistance& slotDistance)
	{
		bool tempIsOccupied = getIsOccupied(idx);
		HashValue tempHash = getHashValue(idx);
		Key tempKey = move(*getKeyPtr(idx));
		Value tempValue = move(*getValuePtr(idx));
		SlotDistance tempSlotDistance = getSlotDistance(idx);

		setHashSlot(idx, isOccupied, hashValue, move(key), move(value), slotDistance);

		isOccupied = tempIsOccupied;
		hashValue = tempHash;
		key = move(tempKey);
		value = move(tempValue);
		slotDistance = tempSlotDistance;
	}
#pragma endregion

	template<typename Key, typename Value, size_t BucketSize>
	const Value* BinHoodBucketNode<Key, Value, BucketSize>::find(HashValue hash, const Key& key) const
	{
		return nullptr;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::getCount(size_t& sizeOut) const
	{
		sizeOut += _count;
		if (hasChildren())
		{
			_left->getCount(sizeOut);
			_right->getCount(sizeOut);
		}
	}

	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
	HashMap<Key, Value, HashBucket, HashConvertor>::~HashMap()
	{
		if (_bucket)
		{
			delete _bucket;
			_bucket = nullptr;
		}
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	void HashMap<Key, Value, Bucket, HashConvertor>::insert(const Key& key, const Value& value)
	{
		size_t hash = _hashConvertor(key);
		_bucket->insert(hash, key, value);
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	void HashMap<Key, Value, Bucket, HashConvertor>::remove(const Key& key)
	{
	}

	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
	const Value* HashMap<Key, Value, Bucket, HashConvertor>::find(const Key& key) const
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