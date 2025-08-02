#pragma once
#include "TypeCommon.h"
#include "TypeLimit.h"
#include "OptionalValue.h"

namespace ke
{
	template<typename Value, size_t BucketSize, float SeperateThreshold, float MergeThreshold>
	class BucketNode
	{
	public:
		explicit BucketNode(size_t from, size_t to, BucketNode* parent, bool isAllocateValues);
		~BucketNode();

	private:
		size_t			_from;
		size_t			_to;
		BucketNode*		_parent = nullptr;
		BucketNode*		_left = nullptr;
		BucketNode*		_right = nullptr;

	private:
		size_t							_count = 0;
		OptionalValue<size_t, Value>*	_values = nullptr;

	public:
		inline bool		isInRange(size_t hash) const;
		inline bool		hasChildren() const;
		inline float	getLoadFactor() const;

	public:
		/* RobinHood Based Insert Process*/
		void	SplitBucket();
		void	InsertValue(size_t hash, const Value& value);

	};

	template<typename Key, typename Value, size_t BucketSize = 64, float SeperateThreshold = 0.8f, float MergeThreshold = 0.6f>
	class HashMap
	{
	private:
		BucketNode<Value, BucketSize, SeperateThreshold, MergeThreshold>* _root = nullptr;

	public:
		void Insert(const Key& key, const Value& value);
		void Remove(const Key& key);
		const OptionalValue<size_t, Value>& Find(const Key& key) const;
	};
}

#include "HashMap.hpp"