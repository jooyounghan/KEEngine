#pragma once
#include "BinHoodBucketNode.h"
#include "AssertManager.h"

namespace ke
{
#pragma region IBinHoodBucketNode
	template<typename Key, typename Value, size_t BucketSize>
	IBinHoodBucketNode<Key, Value, BucketSize>::IBinHoodBucketNode(Depth depth)
		: _depth(depth), _count(0) 
	{
		_isOccupieds.resize(BucketSize, false);
		_hashValues.resize(BucketSize, NULL);
		_slotDistances.resize(BucketSize);
	}

	template<typename Key, typename Value, size_t BucketSize>
	IBinHoodBucketNode<Key, Value, BucketSize>::~IBinHoodBucketNode()
	{
		KEMemory::SafeRelease(_left);
		KEMemory::SafeRelease(_right);
	}

	template<typename Key, typename Value, size_t BucketSize>
	bool IBinHoodBucketNode<Key, Value, BucketSize>::hasChildren() const
	{
		return _left != nullptr;

	}

	template<typename Key, typename Value, size_t BucketSize>
	IBinHoodBucketNode<Key, Value, BucketSize>* IBinHoodBucketNode<Key, Value, BucketSize>::getLeafNode(HashValue hashValue)
	{
		IBinHoodBucketNode<Key, Value>* leafNode = this;
		while (leafNode->hasChildren())
		{
			leafNode = leafNode->isHashPointLeft(hashValue) ? leafNode->_left: leafNode->_right;
		}
		return leafNode;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void IBinHoodBucketNode<Key, Value, BucketSize>::mergeBucket()
	{
		KE_DEBUG_ASSERT(hasChildren() == true, "Cannot merge a bucket that has no children.");

		mergeBucketImpl(_left, this);
		KEMemory::SafeRelease(_left);

		mergeBucketImpl(_right, this);
		KEMemory::SafeRelease(_right);
	}

	template<typename Key, typename Value, size_t BucketSize>
	void IBinHoodBucketNode<Key, Value, BucketSize>::shiftBack(size_t currentIdx)
	{
		while (true)
		{
			size_t nextIdx = (currentIdx + 1) & (BucketSize - 1);

			const IsOccupied& nextIsOccupied = _isOccupieds[nextIdx];
			const SlotDistance& nextSlotDistance = _slotDistances[nextIdx];

			// If the next slot is unoccupied or its slot distance is 0, we are done shifting.
			if (!nextIsOccupied || nextSlotDistance == 0) break;

			moveHashSlot(currentIdx, nextIdx);
			currentIdx = nextIdx;
		}
	}

	template<typename Key, typename Value, size_t BucketSize>
	float IBinHoodBucketNode<Key, Value, BucketSize>::getLoadFactor() const
	{
		static constexpr float kInvBucketSize = 1.0f / static_cast<float>(BucketSize);
		return static_cast<float>(_count) * kInvBucketSize;
	}
#pragma endregion

#pragma region BinHoodKeyBucketNode
	template<typename Key, size_t BucketSize>
	BinHoodKeyBucketNode<Key, BucketSize>::BinHoodKeyBucketNode()
		: IBinHoodBucketNode(0), _parent(nullptr)
	{
		_keys.resize(BucketSize);
	}

	template<typename Key, size_t BucketSize>
	BinHoodKeyBucketNode<Key, BucketSize>::BinHoodKeyBucketNode(Depth depth, BinHoodKeyBucketNode* parent)
		: IBinHoodBucketNode(depth), _parent(parent)
	{
		_keys.resize(BucketSize);
	}

	template<typename Key, size_t BucketSize>
	BinHoodKeyBucketNode<Key, BucketSize>::~BinHoodKeyBucketNode()
	{
	}

	template<typename Key, size_t BucketSize>
	void BinHoodKeyBucketNode<Key, BucketSize>::splitBucket()
	{
		KE_DEBUG_ASSERT(hasChildren() == false, "Bucket already has children, cannot split again.");

		_left = new BinHoodKeyBucketNode<Key, BucketSize>(_depth + 1, this);
		_right = new BinHoodKeyBucketNode<Key, BucketSize>(_depth + 1, this);

		// Rehash all entries into the new child buckets.
		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = _isOccupieds[idx];
			if (!isOccupied) continue;

			const HashValue& hashValue = _hashValues[idx];
			IBinHoodBucketNode<Key, void>* targetNode = isHashPointLeft(hashValue) ? _left : _right;

			HashBucketInsertEntry<Key> insertEntry(hashValue, move(_keys[idx]));
			targetNode->insert(insertEntry));
		}

		_count = 0;
	}

	template<typename Key, size_t BucketSize>
	void BinHoodKeyBucketNode<Key, BucketSize>::mergeBucketImpl(void* childNode, void* parentNode)
	{
		BinHoodKeyBucketNode<Key, BucketSize>* childBucketNode = static_cast<BinHoodKeyBucketNode<Key, BucketSize>*>(childNode);
		BinHoodKeyBucketNode<Key, BucketSize>* parentBucketNode = static_cast<BinHoodKeyBucketNode<Key, BucketSize>*>(parentNode);

		// Rehash all entries from the child bucket into the parent bucket.
		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = childBucketNode->_isOccupieds[idx];
			if (isOccupied == false) continue;

			HashBucketInsertEntry<Key> insertEntry(childBucketNode->_hashValues[idx], move(childBucketNode->_keys[idx]));
			parentBucketNode->insert(insertEntry);
		}
		parentBucketNode->_count += childBucketNode->_count;
	}

	template<typename Key, size_t BucketSize>
	void BinHoodKeyBucketNode<Key, BucketSize>::moveHashSlot(size_t srcIdx, size_t destIdx)
	{
		_isOccupieds[destIdx] = true;
		_hashValues[destIdx] = move(_hashValues[srcIdx]);
		_keys[destIdx] = move(_keys[srcIdx]);
		_slotDistances[destIdx] = _slotDistances[srcIdx] - 1;

		_isOccupieds[srcIdx] = false;
		_slotDistances[srcIdx] = 0;
	}

	template<typename Key, size_t BucketSize>
	void BinHoodKeyBucketNode<Key, BucketSize>::insert(HashBucketInsertEntry<Key>& entry)
	{
		BinHoodKeyBucketNode* leafBucket = static_cast<BinHoodKeyBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = entry._hashValue & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			// If we found an empty slot, insert the new entry here.
			if (leafBucket->_isOccupieds[idx] == false)
			{
				leafBucket->_hashValues[idx] = entry._hashValue;
				leafBucket->_keys[idx] = move(entry._key);
				leafBucket->_slotDistances[idx] = targetSlotDistance;
				++leafBucket->_count;
				break;
			}

			// If we found the same key, update the value.
			const Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == entry._key)
			{
				break;
			}

			// If the current slot distance is less than the target slot distance, swap the entries.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
			{	
				// Swap the entries.
				static HashBucketInsertEntry<Key> stageHashBucketInsertEntry;

				stageHashBucketInsertEntry._hashValue = move(leafBucket->_hashValues[idx]);
				stageHashBucketInsertEntry._key = move(leafBucket->_keys[idx]);
				SlotDistance stageSlotDistance = leafBucket->_slotDistances[idx];

				leafBucket->_hashValues[idx] = move(entry._hashValue);
				leafBucket->_keys[idx] = move(entry._key);
				leafBucket->_slotDistances[idx] = targetSlotDistance;

				entry._hashValue = move(stageHashBucketInsertEntry._hashValue);
				entry._key = move(stageHashBucketInsertEntry._key);
				targetSlotDistance = stageSlotDistance;
			}

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		if (leafBucket->getLoadFactor() > SeperateThreshold)
		{
			leafBucket->splitBucket();
		}
	}

	template<typename Key, size_t BucketSize>
	void BinHoodKeyBucketNode<Key, BucketSize>::remove(HashValue hash, const Key& key)
	{
		BinHoodKeyBucketNode* leafBucket = static_cast<BinHoodKeyBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = hash & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (isOccupied == false) return;

			// If found, remove the entry and shift back the subsequent entries.
			Key& currentKey = leafBucket->_keys[idx];			
			if (currentKey == key)
			{
				currentKey.~Key();
				leafBucket->shiftBack(idx);
				--leafBucket->_count;
				return;
			}

			// If the current slot distance is less than the target slot distance, the key does not exist.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				return;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}
	}

	template<typename Key, size_t BucketSize>
	HashBucketFindResult<Key> BinHoodKeyBucketNode<Key, BucketSize>::find(HashValue hash, const Key& key)
	{
		BinHoodKeyBucketNode* leafBucket = static_cast<BinHoodKeyBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = hash & (BucketSize - 1);

		HashBucketFindResult<Key> result;
		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (!isOccupied) break;

			Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == key)
			{
				result._found = true;
				return result;
			}

			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				break;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		result._found = false;
		return result;
	}
#pragma endregion


#pragma region BinHoodKeyValueBucketNode
	template<typename Key, typename Value, size_t BucketSize>
	BinHoodKeyValueBucketNode<Key, Value, BucketSize>::BinHoodKeyValueBucketNode()
		: BinHoodKeyBucketNode<Key, BucketSize>()
	{
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodKeyValueBucketNode<Key, Value, BucketSize>::BinHoodKeyValueBucketNode(HashValue from, HashValue to, BinHoodKeyValueBucketNode* parent)
		: BinHoodKeyBucketNode<Key, BucketSize>(from, to, parent)
	{
	}

	template<typename Key, typename Value, size_t BucketSize>
	BinHoodKeyValueBucketNode<Key, Value, BucketSize>::~BinHoodKeyValueBucketNode()
	{
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodKeyValueBucketNode<Key, Value, BucketSize>::splitBucket()
	{
		KE_DEBUG_ASSERT(hasChildren() == false, "Bucket already has children, cannot split again.");

		_left = new BinHoodKeyValueBucketNode<Key, Value, BucketSize>(_depth + 1, this);
		_right = new BinHoodKeyValueBucketNode<Key, Value, BucketSize>(_depth + 1, this);

		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = _isOccupieds[idx];
			if (!isOccupied) continue;

			const HashValue& hashValue = _hashValues[idx];
			IBinHoodBucketNode<Key, void>* targetNode = isHashPointLeft(hashValue) ? _left : _right;

			HashBucketInsertEntry<Key, Value> insertEntry;
			insertEntry._hashValue = hashValue;
			insertEntry._key = move(_keys[idx]);
			insertEntry._value = move(_values[idx]);

			targetNode->insert(insertEntry));
		}

		_count = 0;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodKeyValueBucketNode<Key, Value, BucketSize>::mergeBucketImpl(void* childNode, void* parentNode)
	{
		BinHoodKeyValueBucketNode<Key, Value, BucketSize>* childBucketNode = static_cast<BinHoodKeyValueBucketNode<Key, Value, BucketSize>*>(childNode);
		BinHoodKeyValueBucketNode<Key, Value, BucketSize>* parentBucketNode = static_cast<BinHoodKeyValueBucketNode<Key, Value, BucketSize>*>(parentNode);

		for (size_t idx = 0; idx < BucketSize; ++idx)
		{
			const bool& isOccupied = childBucketNode->_isOccupieds[idx];
			if (isOccupied == false) continue;

			HashBucketInsertEntry<Key> insertEntry;
			insertEntry._hashValue = childBucketNode->_hashValues[idx];
			insertEntry._key = move(childBucketNode->_keys[idx]);
			insertEntry._value = move(childBucketNode->_value[idx]);
			parentBucketNode->insert(insertEntry);
		}
		parentBucketNode->_count += childBucketNode->_count;
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodKeyValueBucketNode<Key, Value, BucketSize>::moveHashSlot(size_t srcIdx, size_t destIdx)
	{
		__super::moveHashSlot(srcIdx, destIdx);
		_values[destIdx] = move(_values[srcIdx]);
	}

	template<typename Key, typename Value, size_t BucketSize>
	void BinHoodKeyValueBucketNode<Key, Value, BucketSize>::insert(HashBucketInsertEntry<Key, Value>& entry)
	{
		BinHoodKeyValueBucketNode* leafBucket = static_cast<BinHoodKeyValueBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = entry._hashValue & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			// If we found an empty slot, insert the new entry here.
			if (leafBucket->_isOccupieds[idx] == false)
			{
				leafBucket->_hashValues[idx] = entry._hashValue;
				leafBucket->_keys[idx] = move(entry._key);
				leafBucket->_values[idx] = move(entry._value);
				leafBucket->_slotDistances[idx] = targetSlotDistance;
				++leafBucket->_count;
				break;
			}

			// If we found the same key, update the value.
			const Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == entry._key)
			{
				break;
			}

			// If the current slot distance is less than the target slot distance, swap the entries.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
			{
				// Swap the entries.
				static HashBucketInsertEntry<Key> stageHashBucketInsertEntry;

				stageHashBucketInsertEntry._hashValue = move(leafBucket->_hashValues[idx]);
				stageHashBucketInsertEntry._key = move(leafBucket->_keys[idx]);
				stageHashBucketInsertEntry._value = move(leafBucket->_values[idx]);
				SlotDistance stageSlotDistance = leafBucket->_slotDistances[idx];

				leafBucket->_hashValues[idx] = move(entry._hashValue);
				leafBucket->_keys[idx] = move(entry._key);
				leafBucket->_values[idx] = move(entry._value);
				leafBucket->_slotDistances[idx] = targetSlotDistance;

				entry._hashValue = move(stageHashBucketInsertEntry._hashValue);
				entry._key = move(stageHashBucketInsertEntry._key);
				entry._value = move(stageHashBucketInsertEntry._value);
				targetSlotDistance = stageSlotDistance;
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
	void BinHoodKeyValueBucketNode<Key, Value, BucketSize>::remove(HashValue hash, const Key& key)
	{
		BinHoodKeyBucketNode* leafBucket = static_cast<BinHoodKeyBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = hash & (BucketSize - 1);

		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (isOccupied == false) return;

			// If found, remove the entry and shift back the subsequent entries.
			Key& currentKey = leafBucket->_keys[idx];
			Value& currentValue = leafBucket->_values[idx];
			if (currentKey == key)
			{
				currentKey.~Key();
				currentValue.~Value();
				leafBucket->shiftBack(idx);
				--leafBucket->_count;
				return;
			}

			// If the current slot distance is less than the target slot distance, the key does not exist.
			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				return;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}
	}
	
	template<typename Key, typename Value, size_t BucketSize>
	HashBucketFindResult<Key, Value> BinHoodKeyValueBucketNode<Key, Value, BucketSize>::find(HashValue hash, const Key& key)
	{
		BinHoodKeyValueBucketNode* leafBucket = static_cast<BinHoodKeyValueBucketNode*>(getLeafNode(entry._hashValue));
		size_t idx = hash & (BucketSize - 1);

		HashBucketFindResult<Key, Value> result;
		SlotDistance targetSlotDistance = 0;
		while (true)
		{
			bool& isOccupied = leafBucket->_isOccupieds[idx];
			if (!isOccupied) break;

			Key& currentKey = leafBucket->_keys[idx];
			if (currentKey == key)
			{
				result._found = true;
				result._valuePtr = &leafBucket->_values[idx];
				return result;
			}

			if (leafBucket->_slotDistances[idx] < targetSlotDistance)
				break;

			idx = (idx + 1) & (BucketSize - 1);
			++targetSlotDistance;
		}

		result._found = false;
		return result;
	}
#pragma endregion
}