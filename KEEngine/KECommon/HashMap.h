#pragma once
#include "TypeCommon.h"
#include "HashTraits.h"
#include "TypeLimit.h"
#include "OptionalValue.h"

namespace ke
{

//	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
//	class BinHoodBucketNode
//	{
//		using HashValue = size_t;
//		using SlotDistance = uint8;
//
//	public:
//		class HashSlot : public OptionalValue <HashValue, Value, SlotDistance>
//		{
//			using Base = OptionalValue<HashValue, Value, SlotDistance>;
//
//		public:
//			HashSlot() = default;
//			HashSlot(HashValue hashValue, const Value& value, SlotDistance slotDistance);
//
//			HashSlot(const HashSlot& other);
//			HashSlot(HashSlot&& other);
//			~HashSlot();
//
//			HashSlot& operator=(const HashSlot& other);
//			HashSlot& operator=(HashSlot&& other);
//
//	#ifdef _DEBUG
//		private:
//			HashValue*		_hashValue = nullptr;
//			Value*			_value = nullptr;
//			SlotDistance*	_slotDistance = nullptr;
//
//		private:
//			void bindDebugProperty() noexcept;
//
//	#endif
//		};
//
//	public:
//		explicit BinHoodBucketNode();
//		explicit BinHoodBucketNode(HashValue from, HashValue to, BinHoodBucketNode* parent, bool isAllocateValues);
//		~BinHoodBucketNode();
//
//	private:
//		HashValue			_from;
//		HashValue			_to;
//		BinHoodBucketNode*	_parent = nullptr;
//		BinHoodBucketNode*	_left = nullptr;
//		BinHoodBucketNode*	_right = nullptr;
//
//	private:
//		size_t			_count = 0;
//		HashSlot*		_values = nullptr;
//
//	private:
//		/* RobinHood Based Insert Process*/
//		inline bool		isInRange(HashValue hash) const;
//		inline bool		hasChildren() const;
//		inline float	getLoadFactor() const;
//		void			splitBucket();
//		void			shiftBack(size_t emptyIdx);
//
//	public:
//		/* HashBucket Method Implement */
//		void								insert(HashValue hash, const Value& value);
//		void								remove(HashValue hash);
//		const OptionalValue<size_t, Value>& find(HashValue hash) const;
//		void								getCount(size_t& sizeOut) const;
//
//#ifdef _DEBUG
//	private:
//		static const size_t _bucketSize = BucketSize;
//#endif
//	};
//
//	template<typename Key, typename Value, typename HashBucket, typename HashConvertor>
//	class HashMap
//	{
//		static_assert(KETrait::HashBucketTrait<HashBucket, Value>::value, "Bucket does not satisfy the required HashBucketTrait.");
//		static_assert(KETrait::HashConvertorTrait<HashConvertor, Value>::value, "HashConvertor does not satisfy the required HashConvertorTrait.");
//
//	public:
//		~HashMap();
//
//	private:
//		HashBucket* _bucket = new HashBucket();
//		NO_UNIQUE_ADDRESS HashConvertor _hashConvertor;
//
//	public:
//		void								insert(const Key& key, const Value& value);
//		void								remove(const Key& key);
//		const OptionalValue<size_t, Value>& find(const Key& key) const;
//
//	public:
//		size_t getCount() const;
//	};
}

#include "HashMap.hpp"