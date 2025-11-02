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

	CONSTEXPR_INLINE constexpr static float SeperateThreshold = 0.75f;
	CONSTEXPR_INLINE constexpr static float MergeThreshold = 0.25f;

	template <typename Key, typename Value = void>
	struct HashBucketInsertEntry
	{
		HashValue	_hashValue;
		Key			_key;
		Value		_value;
	};

	template <typename Key>
	struct HashBucketInsertEntry<Key, void>
	{
		HashValue	_hashValue;
		Key			_key;
	};

	template <typename Key, typename Value = void>
	struct HashBucketFindResult
	{
		bool	_found;
		Value*	_valuePtr;
	};

	template <typename Key>
	struct HashBucketFindResult<Key, void>
	{
		bool	_found;
	};

	template<typename Key, typename Value, size_t BucketSize>
	class IBinHoodBucketNode
	{
	public:
		IBinHoodBucketNode(Depth depth);
		virtual ~IBinHoodBucketNode();

	protected:
		virtual void splitBucket() = 0;
		virtual void mergeBucket();
		virtual void mergeBucketImpl(void* childNode, void* parentNode) = 0;

	protected:
		void shiftBack(size_t currentIdx);
		virtual void moveHashSlot(size_t srcIdx, size_t destIdx) = 0;

	public:
		virtual void								insert(HashBucketInsertEntry<Key, Value>& entry) = 0;
		virtual void								remove(HashValue hash, const Key& key) = 0;
		virtual HashBucketFindResult<Key, Value>	find(HashValue hash, const Key& key) = 0;

	public:
		IBinHoodBucketNode*			getLeafNode(HashValue hashValue);
		bool						hasChildren() const;


	protected:
		IBinHoodBucketNode* _parent = nullptr;
		IBinHoodBucketNode* _left = nullptr;
		IBinHoodBucketNode* _right = nullptr;

	protected:
		Depth					_depth;
		size_t					_count;

	protected:
		Vector<IsOccupied>		_isOccupieds;
		Vector<HashValue>		_hashValues;
		Vector<SlotDistance>	_slotDistances;

	protected:
		Depth depth() const { return _depth; }
		size_t count() const { return _count; }
		bool isHashPointLeft(HashValue hash) const { return ((hash >> _depth) & 1) == 0; }

	protected:
		float getLoadFactor() const;

	protected:
#ifdef _DEBUG
		size_t _bucketSize = BucketSize;
#endif // _DEBUG
	};

	template<typename Key, size_t BucketSize>
	class BinHoodKeyBucketNode : public IBinHoodBucketNode<Key, void>
	{

	public:
		BinHoodKeyBucketNode();
		BinHoodKeyBucketNode(Depth depth, BinHoodKeyBucketNode* parent);
		~BinHoodKeyBucketNode() override;

	protected:
		virtual void splitBucket() override;
		virtual void mergeBucketImpl(void* childNode, void* parentNode) override;

	protected:
		virtual void moveHashSlot(size_t srcIdx, size_t destIdx) override;

	public:
		/* HashBucket Method Implement */
		virtual void						insert(HashBucketInsertEntry<Key>& entry) override;
		virtual void						remove(HashValue hash, const Key& key) override;
		virtual HashBucketFindResult<Key>	find(HashValue hash, const Key& key) override;
	
	protected:
		Vector<Key>				_keys;

		static_assert(KETrait::IsPowerOfTwo<size_t, BucketSize>::value, "BucketSize must be a power of two.");
	};

	template<typename Key, typename Value, size_t BucketSize>
	class BinHoodKeyValueBucketNode : public BinHoodKeyBucketNode<Key, BucketSize>
	{
	public:
		BinHoodKeyValueBucketNode();
		BinHoodKeyValueBucketNode(HashValue from, HashValue to, BinHoodKeyValueBucketNode* parent);
		~BinHoodKeyValueBucketNode() override;

	protected:
		virtual void splitBucket() override;
		virtual void mergeBucketImpl(void* childNode, void* parentNode) override;

	protected:
		virtual void moveHashSlot(size_t srcIdx, size_t destIdx) override;

	protected:
		Vector<Value>			_values;

	public:
		/* HashBucket Method Implement */
		virtual void								insert(HashBucketInsertEntry<Key, Value>& entry) override;
		virtual void								remove(HashValue hash, const Key& key) override;
		virtual HashBucketFindResult<Key, Value>	find(HashValue hash, const Key& key) override;
	};
}
#include "BinHoodBucketNode.hpp"