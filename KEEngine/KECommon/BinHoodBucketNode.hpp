#pragma once
#include "BinHoodBucketNode.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode()
		: _from(0), _to(KELimit::getMax<HashValue>()), _mid(KELimit::getMax<HashValue>() / 2)
	{
		_values = new StaticColumnarArray<BucketSize, IsOccupied, HashValue, Key, Value, SlotDistance>();
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent)
		: _from(from), _to(to), _parent(parent)
	{
		_mid = _from + (_to - _from) / 2;
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
	BinHoodBucketNode<Key, Value, BucketSize>* BinHoodBucketNode<Key, Value, BucketSize>::getLeafBucket(HashValue hashValue)
	{
		BinHoodBucketNode* leaf = this;
		while (leaf->hasChildren())
		{
			leaf = (hashValue <= leaf->_mid) ? leaf->_left : leaf->_right;
		}
		return leaf;
	}

	template<typename Key, typename Value, size_t BucketSize>
	bool BinHoodBucketNode<Key, Value, BucketSize>::hasChildren() const
	{
		return _left != nullptr;
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

		_left = new BinHoodBucketNode(_from, _mid, this);
		_right = new BinHoodBucketNode(_mid + 1, _to, this);

		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			bool& isOccupied = getIsOccupied(idx);
			HashValue hashValue = getHashValue(idx);
			Key& key = *getKeyPtr(idx);
			Value& value = *getValuePtr(idx);

			if (!isOccupied) continue;

			BinHoodBucketNode* destNode = hashValue <= _mid ? _left : _right;
			destNode->insert(hashValue, move(key), move(value));

			isOccupied = false;
			_count--;
		}
		KEMemory::SafeRelease(_values);
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::mergeBucket()
	{
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::shiftBack(size_t currentIdx)
	{
		while (true)
		{
			int nextIdx = (currentIdx + 1) & (BucketSize - 1);

			IsOccupied& nextIsOccupied = getIsOccupied(nextIdx);
			SlotDistance& nextSlotDistance = getSlotDistance(nextIdx);

			if (!nextIsOccupied || nextSlotDistance == 0) break;

			setHashSlot(currentIdx, true, getHashValue(nextIdx), move(*getKeyPtr(nextIdx)), move(*getValuePtr(nextIdx)), nextSlotDistance - 1);
			nextIsOccupied = false;
			nextSlotDistance = 0;

			currentIdx = nextIdx;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::insert(HashValue hash, const Key& key, const Value& value)
	{
		BinHoodBucketNode* leafBucket = getLeafBucket(hash);

		size_t idx = hash & (BucketSize - 1);

		bool targetIsOccupied = true;
		HashValue targetHash = hash;
		Key targetKey = move(key);
		Value targetValue = move(value);
		SlotDistance targetSlotDistance = 0;

		while (true)
		{
			bool& isCurrentOccupied = leafBucket->getIsOccupied(idx);
			if (isCurrentOccupied == false)
			{
				leafBucket->setHashSlot(idx, targetIsOccupied, targetHash, move(targetKey), move(targetValue), targetSlotDistance);
				++leafBucket->_count;
				break;
			}

			Key& currentKey = *(leafBucket->getKeyPtr(idx));

			if (currentKey == targetKey)
			{
				leafBucket->setHashSlot(idx, move(targetValue));
				break;
			}

			SlotDistance currentDistance = leafBucket->getSlotDistance(idx);
			if (currentDistance < targetSlotDistance)
			{
				leafBucket->swapHashSlot(idx, targetIsOccupied, targetHash, targetKey, targetValue, targetSlotDistance);
			}

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		if (leafBucket->getLoadFactor() > SeperateThreshold)
		{
			leafBucket->splitBucket();
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::remove(HashValue hash, const Key& key)
	{
		BinHoodBucketNode* leafBucket = getLeafBucket(hash);

		size_t idx = hash & (BucketSize - 1);
		SlotDistance slotDistance = 0;

		while (true)
		{
			bool& isOccupied = leafBucket->getIsOccupied(idx);
			if (!isOccupied)
				return;

			Key& currentKey = *(leafBucket->getKeyPtr(idx));
			if (currentKey == key)
			{
				Value& currentValue = *(leafBucket->getValuePtr(idx));

				isOccupied = false;
				currentKey.~Key();
				currentValue.~Value();

				leafBucket->shiftBack(idx);
				--_count;
				return;
			}

			SlotDistance& currentSlotDistance = leafBucket->getSlotDistance(idx);
			if (currentSlotDistance < slotDistance)
				return;

			idx = (idx + 1) & (BucketSize - 1);
			++slotDistance;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	bool BinHoodBucketNode<Key, Value, BucketSize>::find(HashValue hash, const Key& key, Key*& foundKey, Value*& foundValue)
	{
		BinHoodBucketNode* leafBucket = getLeafBucket(hash);

		size_t idx = hash & (BucketSize - 1);
		SlotDistance slotDistance = 0;

		while (true)
		{
			bool& isOccupied = leafBucket->getIsOccupied(idx);
			if (!isOccupied)
				break;

			Key& currentKey = *(leafBucket->getKeyPtr(idx));
			if (currentKey == key)
			{
				foundKey = &currentKey;
				foundValue = leafBucket->getValuePtr(idx);
				return leafBucket->getValuePtr(idx);
			}

			SlotDistance& currentSlotDistance = leafBucket->getSlotDistance(idx);
			if (currentSlotDistance < slotDistance)
				break;

			idx = (idx + 1) & (BucketSize - 1);
			++slotDistance;
		}

		foundKey = nullptr;
		foundValue = nullptr;
		return false;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::count(size_t& sizeOut) const
	{
		sizeOut += _count;
		if (hasChildren())
		{
			_left->count(sizeOut);
			_right->count(sizeOut);
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
}