#pragma once
#include "TypeCommon.h"
#include "TypeLimit.h"
#include "Vector.h"
#include "HashTraits.h"

namespace ke
{
	using Depth = uint8;
	using IsOccupied = bool;
	using HashValue = size_t;
	using SlotDistance = uint8;

	CONSTEXPR_INLINE constexpr static HashValue INVALID_HASH_VALUE = 0u;
	CONSTEXPR_INLINE constexpr static float HASH_BUCKET_MERGE_THRESHOLD = 0.25f;

	template <typename Key, typename Value = void>
	struct HashBucketInsertEntry
	{
		HashValue																			_hashValue;
		Key																					_key;
		KETrait::ConditionalType<KETrait::IsVoid<Value>::value, KETrait::EmptyType, Value>	_value;
	};

	template <typename Key, typename Value = void>
	struct HashBucketFindResult
	{
		Key*																				_keyPtr;
		KETrait::ConditionalType<KETrait::IsVoid<Value>::value, KETrait::EmptyType, Value*>	_valuePtr;
	};

	template<typename Key, typename Value, size_t BucketSize>
	class BinHoodBucketNode
	{
	public:
		BinHoodBucketNode();
		BinHoodBucketNode(Depth depth, BinHoodBucketNode* parent);
		~BinHoodBucketNode();

	public:
		BinHoodBucketNode*			getLeafNode(HashValue hashValue);
		bool						hasChildren() const;

	private:
		HashBucketInsertEntry<Key, Value> createMovedInsertEntry(size_t idx);

	protected:
		void splitBucket();
		void mergeBucket();
		void mergeBucketImpl(BinHoodBucketNode* child, BinHoodBucketNode* parent);

	protected:
		void shiftBack(size_t currentIdx);

	public:
		void								insert(HashBucketInsertEntry<Key, Value>& entry);
		void								remove(HashValue hash, const Key& key);
		HashBucketFindResult<Key, Value>	find(HashValue hash, const Key& key);

	protected:
		BinHoodBucketNode* _parent = nullptr;
		BinHoodBucketNode* _left = nullptr;
		BinHoodBucketNode* _right = nullptr;

	protected:
		Vector<IsOccupied>																			_isOccupieds;
		Vector<HashValue>																			_hashValues;
		Vector<SlotDistance>																		_slotDistances;
		Vector<Key>																					_keys;
		KETrait::ConditionalType<KETrait::IsVoid<Value>::value, KETrait::EmptyType, Vector<Value>>	_values;

	protected:
		Depth					_depth;
		size_t					_count;

	protected:
		Depth depth() const { return _depth; }
		size_t count() const { return _count; }
		size_t capacity() const { return BucketSize; }
		bool isHashPointLeft(HashValue hash) const { return ((hash >> _depth) & 1) == 0; }

	public:
		void getTotalSubCount(size_t& outCount) const;

	protected:
		float getLoadFactor() const;

	protected:
#ifdef _DEBUG
		size_t _bucketSize = BucketSize;
#endif // _DEBUG
	};
}
#include "BinHoodBucketNode.hpp"