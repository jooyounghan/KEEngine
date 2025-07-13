#pragma once
#include "MethodTraits.h"

namespace ke
{
	struct MemoryEntry
	{
		explicit MemoryEntry(void* address = nullptr, size_t count = 0)
			: _address(address), _count(count)
		{
		}
		void* _address;
		size_t	_count;
	};

	namespace KETrait
	{
		DEFINE_METHOD_TRAIT(HasAllocate, allocate);
		DEFINE_METHOD_TRAIT(HasDeallocate, deallocate);

		template<typename Allocator>
		struct AllocatorTrait : TraitCondition<
			SatisfyAll<
				CHECK_METHOD_TRAIT(HasAllocate, Allocator, MemoryEntry, const size_t),
				CHECK_METHOD_TRAIT(HasDeallocate, Allocator, void, MemoryEntry&)
			>::value, TrueTrait, FalseTrait>::Type
		{
		};
	};

}