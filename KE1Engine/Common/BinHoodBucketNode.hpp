#pragma once
#include "BinHoodBucketNode.h"
#include "AssertManager.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode()
		: _parent(nullptr), _depth(0), _count(0)
	{
		_isOccupieds.resize(BucketSize, false);
		_hashValues.resize(BucketSize, INVALID_HASH_VALUE);
		_slotDistances.resize(BucketSize);
		_keys.resize(BucketSize);
		if constexpr (KETrait::IsVoid<Value>::value == false)
		{
			_values.resize(BucketSize);
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::BinHoodBucketNode(Depth depth, BinHoodBucketNode* parent)
		: _parent(parent), _depth(depth), _count(0)
	{
		_isOccupieds.resize(BucketSize, false);
		_hashValues.resize(BucketSize, INVALID_HASH_VALUE);
		_slotDistances.resize(BucketSize);
		_keys.resize(BucketSize);
		if constexpr (KETrait::IsVoid<Value>::value == false)
		{
			_values.resize(BucketSize);
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>::~BinHoodBucketNode()
	{
		KEMemory::SafeRelease(_left);
		KEMemory::SafeRelease(_right);
	}

	template<typename Key, typename Value, size_t BucketSize>
	bool BinHoodBucketNode<Key, Value, BucketSize>::hasChildren() const
	{
		return _left != nullptr;

	}

	template<typename Key, typename Value, size_t BucketSize>
	HashBucketInsertEntry<Key, Value> BinHoodBucketNode<Key, Value, BucketSize>::createMovedInsertEntry(size_t idx)
	{
		if constexpr (KETrait::IsVoid<Value>::value)
		{
			HashBucketInsertEntry<Key> insertEntry(_hashValues[idx], move(_keys[idx]));
			return insertEntry;
		}
		else
		{
			HashBucketInsertEntry<Key, Value> insertEntry(_hashValues[idx], move(_keys[idx]), move(_values[idx]));
			return insertEntry;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodBucketNode<Key, Value, BucketSize>* BinHoodBucketNode<Key, Value, BucketSize>::getLeafNode(HashValue hashValue)
	{
		BinHoodBucketNode* leafNode = this;
		while (leafNode->hasChildren())
		{
			leafNode = leafNode->isHashPointLeft(hashValue) ? leafNode->_left: leafNode->_right;
		}
		return leafNode;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::splitBucket()
	{
		KE_DEBUG_ASSERT(hasChildren() == false, "Bucket already has children, cannot split again.");

		const Depth childDepth = static_cast<Depth>(_depth + 1);
		_left = new BinHoodBucketNode<Key, Value, BucketSize>(childDepth, this);
		_right = new BinHoodBucketNode<Key, Value, BucketSize>(childDepth, this);

		// Rehash all entries into the new child buckets.
		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = _isOccupieds[idx];
			if (!isOccupied) continue;

			const HashValue& hashValue = _hashValues[idx];
			BinHoodBucketNode<Key, Value, BucketSize>* targetNode = isHashPointLeft(hashValue) ? _left : _right;

			HashBucketInsertEntry<Key, Value> insertEntry = createMovedInsertEntry(idx);
			targetNode->insert(insertEntry);
		}

		_count = 0;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::mergeBucket()
	{
		KE_DEBUG_ASSERT(hasChildren() == true, "Cannot merge a bucket that has no children.");

		BinHoodBucketNode* left = _left;
		BinHoodBucketNode* right = _right;
		_left = _right = nullptr;

		mergeBucketImpl(left, this);
		KEMemory::SafeRelease(left);

		mergeBucketImpl(right, this);
		KEMemory::SafeRelease(right);
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::mergeBucketImpl(BinHoodBucketNode* child, BinHoodBucketNode* parent)
	{
		// Rehash all entries from the child bucket into the parent bucket.
		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = child->_isOccupieds[idx];
			if (isOccupied == false) continue;

			HashBucketInsertEntry<Key, Value> insertEntry = child->createMovedInsertEntry(idx);
			parent->insert(insertEntry);
		}
		parent->_count += child->_count;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::shiftBack(size_t currentIdx)
	{
		while (true)
		{
			size_t nextIdx = (currentIdx + 1) & (BucketSize - 1);

			const IsOccupied& nextIsOccupied = _isOccupieds[nextIdx];
			const SlotDistance& nextSlotDistance = _slotDistances[nextIdx];

			// If the next slot is unoccupied or its slot distance is 0, we are done shifting.
			if (!nextIsOccupied || nextSlotDistance == 0) break;

			// Move the next slot to the current slot.
			_isOccupieds[currentIdx] = true;
			_hashValues[currentIdx] = move(_hashValues[nextIdx]);
			_keys[currentIdx] = move(_keys[nextIdx]);
			if constexpr (KETrait::IsVoid<Value>::value == false)
			{
				_values[currentIdx] = move(_values[nextIdx]);
			}
			_slotDistances[currentIdx] = _slotDistances[nextIdx] - 1;

			_isOccupieds[nextIdx] = false;
			_slotDistances[nextIdx] = 0;

			currentIdx = nextIdx;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::getTotalSubCount(size_t& outCount) const
	{
		outCount += _count;
		if (hasChildren())
		{
			_left->getTotalSubCount(outCount);
			_right->getTotalSubCount(outCount);
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	float BinHoodBucketNode<Key, Value, BucketSize>::getLoadFactor() const
	{
		static constexpr float kInvBucketSize = 1.0f / static_cast<float>(BucketSize);
		return static_cast<float>(_count) * kInvBucketSize;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::insert(HashBucketInsertEntry<Key, Value>& entry)
	{
		BinHoodBucketNode* leafBucket = getLeafNode(entry._hashValue);
		size_t idx = entry._hashValue & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			// If we found an empty slot, insert the new entry here.
			if (leafBucket->_isOccupieds[idx] == false)
			{
				leafBucket->_isOccupieds[idx] = true;
				leafBucket->_hashValues[idx] = move(entry._hashValue);
				leafBucket->_keys[idx] = move(entry._key);
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					leafBucket->_values[idx] = move(entry._value);
				}
				leafBucket->_slotDistances[idx] = targetSlotDistance;
				++leafBucket->_count;
				break;
			}

			// If we found the same key, update the value.
			const Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == entry._key)
			{
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					leafBucket->_values[idx] = move(entry._value);
				}
				break;
			}

			// If the current slot distance is less than the target slot distance, swap the entries.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
			{
				// Swap the entries.
				HashBucketInsertEntry<Key, Value> stageHashBucketInsertEntry = leafBucket->createMovedInsertEntry(idx);
				SlotDistance stageSlotDistance = leafBucket->_slotDistances[idx];

				leafBucket->_hashValues[idx] = move(entry._hashValue);
				leafBucket->_keys[idx] = move(entry._key);
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					leafBucket->_values[idx] = move(entry._value);
				}
				leafBucket->_slotDistances[idx] = targetSlotDistance;

				entry._hashValue = move(stageHashBucketInsertEntry._hashValue);
				entry._key = move(stageHashBucketInsertEntry._key);
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					entry._value = move(stageHashBucketInsertEntry._value);
				}
				targetSlotDistance = stageSlotDistance;
			}

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		if (leafBucket->getLoadFactor() >= HASH_BUCKET_SPLIT_THRESHOLD)
		{
			leafBucket->splitBucket();
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::remove(HashValue hash, const Key& key)
	{
		BinHoodBucketNode* leafBucket = getLeafNode(hash);
		size_t idx = hash & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (isOccupied == false) break;

			// If found, remove the entry and shift back the subsequent entries.
			Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == key)
			{
				isOccupied = false;
				currentKey.~Key();
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					Value& currentValue = leafBucket->_values[idx];
					currentValue.~Value();
				}

				leafBucket->shiftBack(idx);
				--leafBucket->_count;
				break;
			}

			// If the current slot distance is less than the target slot distance, the key does not exist.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				break;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		if (leafBucket->getLoadFactor() < HASH_BUCKET_MERGE_THRESHOLD)
		{
			leafBucket->mergeBucket();
		}
	}
	
	template<typename Key, typename Value, size_t BucketSize>
	HashBucketFindResult<Key, Value> BinHoodBucketNode<Key, Value, BucketSize>::find(HashValue hash, const Key& key)
	{
		BinHoodBucketNode* leafBucket = getLeafNode(hash);
		size_t idx = hash & (BucketSize - 1);

		HashBucketFindResult<Key, Value> result;
		result._keyPtr = nullptr;
		if constexpr (KETrait::IsVoid<Value>::value == false)
		{
			result._valuePtr = nullptr;
		}

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			const bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (!isOccupied) break;

			Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == key)
			{
				result._keyPtr = &currentKey;
				if constexpr (KETrait::IsVoid<Value>::value == false)
				{
					Value& currentValue = leafBucket->_values[idx];
					result._valuePtr = &currentValue;
				}
				return result;
			}

			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				break;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		return result;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodBucketNode<Key, Value, BucketSize>::insertLocal(HashBucketInsertEntry<Key, Value>& entry)
	{
		size_t idx = entry._hashValue & (BucketSize - 1);
		SlotDistance dist = 0;
		while (_isOccupieds[idx]) {
			++idx;
			++dist;
			if (idx >= BucketSize) idx = 0;
		}
		_isOccupieds[idx] = true;
		_hashValues[idx] = entry._hashValue;
		_keys[idx] = entry._key;
		if constexpr (!KETrait::IsVoid<Value>::value)
			_values[idx] = entry._value;
		_slotDistances[idx] = dist;
		++_count;
	}
#pragma endregion
}