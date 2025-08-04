#pragma once
#include "TypeCommon.h"
#include "ContainerTraits.h"
#include "TypeLimit.h"
#include "OptionalValue.h"

namespace ke
{
	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	class BinHoodBucketNode
	{
	public:
		explicit BinHoodBucketNode(size_t from, size_t to, BinHoodBucketNode* parent, bool isAllocateValues);
		~BinHoodBucketNode();

	private:
		size_t					_from;
		size_t					_to;
		BinHoodBucketNode*		_parent = nullptr;
		BinHoodBucketNode*		_left = nullptr;
		BinHoodBucketNode*		_right = nullptr;

	private:
		size_t							_count = 0;
		OptionalValue<size_t, Value>*	_values = nullptr;

	private:
		/* RobinHood Based Insert Process*/
		inline bool		isInRange(size_t hash) const;
		inline bool		hasChildren() const;
		inline float	getLoadFactor() const;
		void			splitBucket();

	public:
		/* HashBucket Method Implement */
		void								insert(size_t hash, const Value& value);
		void								remove(size_t hash);
		const OptionalValue<size_t, Value>& find(size_t hash) const;
	};

	template<typename Key, typename Value, typename HashBucket>
	class HashMap
	{
		static_assert(KETrait::HashBucketTrait<HashBucket, Value>::value, "Bucket does not satisfy the required HashBucketTrait.");

	private:
		HashBucket* _bucket = nullptr;

	public:
		void								insert(const Key& key, const Value& value);
		void								remove(const Key& key);
		const OptionalValue<size_t, Value>& find(const Key& key) const;
	};
}

#include "HashMap.hpp"