#pragma once
#include "TypeCommon.h"
#include "TypeLimit.h"
#include "HashTraits.h"
#include "HashGenerator.h"
#include "StaticColumnarArray.h"

namespace ke
{
	template<typename Key, typename Value, size_t BucketSize>
	class BinHoodBucketNode
	{
		using IsOccupied = bool;
		using HashValue = size_t;
		using SlotDistance = uint8;
		CONSTEXPR_INLINE constexpr static float SeperateThreshold = 0.75f;
		CONSTEXPR_INLINE constexpr static float MergeThreshold = 0.25f;

	public:
		BinHoodBucketNode();
		BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent, bool isAllocateValues);
		~BinHoodBucketNode();

	private:
		HashValue			_from;
		HashValue			_to;
		BinHoodBucketNode*	_parent = nullptr;
		BinHoodBucketNode*	_left = nullptr;
		BinHoodBucketNode*	_right = nullptr;

	private:
		/* RobinHood Based Insert Process*/
		inline bool		isInRange(HashValue hash) const;
		inline bool		hasChildren() const;
		inline float	getLoadFactor() const;
		void			splitBucket();
		void			shiftBack(size_t emptyIdx);

	public:
		/* HashBucket Method Implement */
		void								insert(HashValue hash, const Key& key, const Value& value);
		void								remove(HashValue hash, const Key& key);
		const Value*						find(HashValue hash, const Key& key) const;
		void								getCount(size_t& sizeOut) const;

	private:
		size_t _count = 0;
		StaticColumnarArray<BucketSize, IsOccupied, HashValue, Key, Value, SlotDistance>* _values = nullptr;
		
#pragma region Helper
	private:
		inline bool&			getIsOccupied(size_t idx) const;
		inline HashValue&		getHashValue(size_t idx) const;	
		inline Key*				getKeyPtr(size_t idx);
		inline Value*			getValuePtr(size_t idx);
		inline SlotDistance&	getSlotDistance(size_t idx) const;

	private:
		inline void				setHashSlot(size_t idx, const Value& value);
		inline void				setHashSlot(size_t idx, Value&& value);
		inline void				setHashSlot(size_t idx, bool isOccupied, HashValue hashValue, const Key& key, const Value& value, SlotDistance distance);
		inline void 			setHashSlot(size_t idx, bool isOccupied, HashValue hashValue, Key&& key, Value&& value, SlotDistance distance);
		inline void				swapHashSlot(size_t idx, bool& isOccupied, HashValue& hashValue, Key& key, Value& value, SlotDistance& slotDistance);

#ifdef _DEBUG
		size_t _bucketSize = BucketSize;
#endif // _DEBUG


#pragma endregion
	};

	template<typename Key, typename Value, typename HashBucket = BinHoodBucketNode<Key, Value, 64>, typename HashConvertor = HashGenerator<Key>>
	class HashMap
	{
	public:
		~HashMap();

	private:
		HashBucket* _bucket = new HashBucket();
		NO_UNIQUE_ADDRESS HashConvertor _hashConvertor;

	public:
		void								insert(const Key& key, const Value& value);
		void								remove(const Key& key);
		const Value*						find(const Key& key) const;

	public:
		size_t getCount() const;

		// Static Asserts
		static_assert(KETrait::HashBucketTrait<HashBucket, Key, Value>::value, "Bucket does not satisfy the required HashBucketTrait.");
		static_assert(KETrait::HashConvertorTrait<HashConvertor, Key>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");

	};

	template<typename Key, typename Value, typename HashConvertor>
	using CompactHashMap = HashMap<Key, Value, BinHoodBucketNode<Key, Value, 64>, HashConvertor>;
}

#include "HashMap.hpp"