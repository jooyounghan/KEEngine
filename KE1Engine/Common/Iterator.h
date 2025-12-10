#pragma once
#include "MethodTraits.h"

namespace ke
{
	namespace KETrait
	{
		DEFINE_METHOD_TRAIT(HasIncrement, operator++);
		DEFINE_METHOD_TRAIT(HasDerefernce, operator*);
		DEFINE_METHOD_TRAIT_WITH_QUALIFIER(HasInequality, operator!=, const);

		template<typename Iterator, typename T>
		struct IteratorTrait : TraitCondition<
			SatisfyAll<
			CHECK_METHOD_TRAIT(HasIncrement, Iterator, Iterator&),
			CHECK_METHOD_TRAIT(HasDerefernce, Iterator, T&),
			CHECK_METHOD_TRAIT(HasInequality, Iterator, bool, const Iterator&)
			>::value, TrueTrait, FalseTrait
		>::Type
		{
		};
	}

	template<typename T>
	class Iterator
	{
	public:
		Iterator(T& target);
		~Iterator() = default;

	private:
		T* _targetAddress;

	public:
		Iterator operator++();
		T& operator*();
		bool operator!=(const Iterator& other) const;
	};

	template<typename T>
	class ConstIterator
	{
	public:
		ConstIterator(T& target);
		~ConstIterator() = default;

	private:
		const T* _targetAddress;

	public:
		ConstIterator operator++();
		const T& operator*();
		bool operator!=(const ConstIterator& other) const;
	};
}