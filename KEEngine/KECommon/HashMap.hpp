#pragma once
#include "HashMap.h"
#include "HashConvertor.h"

namespace ke
{
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::HashSlot(HashValue hashValue, const Value& value, SlotDistance slotDistance)
//		: OptionalValue<HashValue, Value, SlotDistance>(hashValue, value, slotDistance)
//	{
//#ifdef _DEBUG
//		bindDebugProperty();
//#endif
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::HashSlot(const HashSlot& other)
//		: Base(other)
//	{
//#ifdef _DEBUG
//		bindDebugProperty();
//#endif
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::HashSlot(HashSlot&& other)
//		: Base(move(other))
//	{
//#ifdef _DEBUG
//		bindDebugProperty();
//#endif
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::~HashSlot()
//	{
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::bindDebugProperty() noexcept
//	{
//		_hashValue = reinterpret_cast<HashValue*>(&__super::_storage[KEMemory::getOffset<0, HashValue, Value, SlotDistance>()]);
//		_value = reinterpret_cast<Value*>(&__super::_storage[KEMemory::getOffset<1, HashValue, Value, SlotDistance>()]);
//		_slotDistance = reinterpret_cast<SlotDistance*>(&__super::_storage[KEMemory::getOffset<2, HashValue, Value, SlotDistance>()]);
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot& BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::operator=(const HashSlot& other)
//	{
//		__super::operator=(other);
//#ifdef _DEBUG
//		bindDebugProperty();
//#endif
//		return *this;
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot& BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::HashSlot::operator=(HashSlot&& other)
//	{
//		__super::operator=(move(other));
//#ifdef _DEBUG
//		bindDebugProperty();
//#endif
//		return *this;
//	}
//	
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::BinHoodBucketNode()
//		: _from(0), _to(KELimit::getMax<size_t>()), _parent(nullptr)
//	{
//		_values = new HashSlot[BucketSize];
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent, bool isAllocateValues)
//		: _from(from), _to(to), _parent(parent)
//	{
//		if (isAllocateValues)
//			_values = new HashSlot[BucketSize];
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::~BinHoodBucketNode()
//	{
//		if (_left != nullptr)
//		{
//			delete _left;
//			_left = nullptr;
//		}
//
//		if (_right != nullptr)
//		{
//			delete _right;
//			_right = nullptr;
//		}
//
//		if (_values != nullptr)
//		{
//			delete _values;
//			_values = nullptr;
//		}
//	}
//	
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	inline bool BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::isInRange(HashValue hash) const
//	{
//		return _from <= hash && hash <= _to;
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	bool BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::hasChildren() const
//	{
//		return _left != nullptr || _right != nullptr;
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	float BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::getLoadFactor() const
//	{
//		return static_cast<float>(_count) / static_cast<float>(BucketSize);
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::splitBucket()
//	{
//		if (hasChildren()) return;
//
//		HashValue mid = (_from + _to) / 2;
//
//		// left node dosen't initialize slots but moved from parent
//		_left = new BinHoodBucketNode(_from, mid, this, false);
//		_left->_count = _count;
//		_left->_values = _values;
//		
//		_count = 0;
//		_values = nullptr;
//
//		// right node initialize slots
//		_right = new BinHoodBucketNode(mid + 1, _to, this, true);
//
//		for (size_t i = 0; i < BucketSize; ++i)
//		{
//			HashSlot& currentOptionalValue = _left->_values[i];
//			if (currentOptionalValue.hasValue())
//			{
//				const HashValue&	hashValue = *currentOptionalValue.tryGetValue<0>();
//				const Value&		value = *currentOptionalValue.tryGetValue<1>();
//
//				if (_right->isInRange(hashValue))
//				{
//					_right->insert(hashValue, value);
//					_left->remove(hashValue);
//				}
//			}
//		}
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::shiftBack(size_t emptyIdx)
//	{
//		int nextIdx = (emptyIdx + 1) % BucketSize;
//		while (_values[nextIdx].hasValue() && 0 < *_values[nextIdx].tryGetValue<2>())
//		{
//			_values[emptyIdx] = _values[nextIdx];
//			_values[emptyIdx].setValue<2>(*_values[emptyIdx].tryGetValue<2>() - 1);
//
//			_values[nextIdx].~HashSlot();
//			emptyIdx = nextIdx;
//			nextIdx = (nextIdx + 1) % BucketSize;
//		}
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::insert(HashValue hash, const Value& value)
//	{
//		if (hasChildren())
//		{
//			if (_left->isInRange(hash))
//			{
//				_left->insert(hash, value);
//				return;
//			}
//			else
//			{
//				_right->insert(hash, value);
//				return;
//			}
//		}
//
//		size_t idx = hash % BucketSize;
//		HashSlot incoming(hash, value, 0);
//
//		while (true) 
//		{
//			if (!_values[idx].hasValue())
// {
//				_values[idx] = incoming;
//				++_count;
//				break;
//			}
//
//			HashValue currentHash = *(_values[idx].tryGetValue<0>());
//			if (currentHash == hash)
//			{
//				_values[idx].setValue<1>(value);
//				break;
//			}
//
//			SlotDistance currentDistance = *(_values[idx].tryGetValue<2>());
//			SlotDistance incomingDistance = *(incoming.tryGetValue<2>());
//			if (currentDistance < incomingDistance)
//			{
//				HashSlot temp = move(_values[idx]);
//				_values[idx] = incoming;
//				incoming = move(temp);
//			}
//
//			idx = (idx + 1) % BucketSize;
//			incoming.setValue<2>(currentDistance + 1);
//		}
//
//		if (getLoadFactor() > SeperateThreshold)
//		{
//			splitBucket();
//		}
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::remove(HashValue hash)
//	{
//		size_t idx = hash % BucketSize;
//		SlotDistance slotDistance = 0;
//
//		while (_values[idx].hasValue())
//		{
//			if (*_values[idx].tryGetValue<0>() == hash)
//			{
//				_values[idx].~HashSlot();
//				shiftBack(idx);
//				--_count;
//				return;
//			}
//
//			if (*_values[idx].tryGetValue<2>() < slotDistance)
//				return;
//
//			idx = (idx + 1) % BucketSize;
//			++slotDistance;
//		}
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	const OptionalValue<size_t, Value>& BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::find(HashValue hash) const
//	{
//		// TODO: 여기에 return 문을 삽입합니다.
//	}
//
//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	void BinHoodBucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>::getCount(size_t& sizeOut) const
//	{
//		sizeOut += _count;
//		if (hasChildren())
//		{
//			_left->getCount(sizeOut);
//			_right->getCount(sizeOut);
//		}
//	}
//
//	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
//	HashMap<Key, Value, HashBucket, HashConvertor>::~HashMap()
//	{
//		if (_bucket)
//		{
//			delete _bucket;
//			_bucket = nullptr;
//		}
//	}
//
//	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
//	void HashMap<Key, Value, Bucket, HashConvertor>::insert(const Key& key, const Value& value)
//	{
//		size_t hash = _hashConvertor(key);
//		_bucket->insert(hash, value);
//	}
//
//	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
//	void HashMap<Key, Value, Bucket, HashConvertor>::remove(const Key& key)
//	{
//	}
//
//	template<typename Key, typename Value, typename Bucket, typename HashConvertor>
//	const OptionalValue<size_t, Value>& HashMap<Key, Value, Bucket, HashConvertor>::find(const Key& key) const
//	{
//	}
//	
//	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
//	size_t HashMap<Key, Value, HashBucket, HashConvertor>::getCount() const 
//	{ 
//		size_t result = 0; 
//		_bucket->getCount(result); 
//		return result; 
//	}
}