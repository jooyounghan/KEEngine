#pragma once
#include "MethodTraits.h"

namespace ke
{
	struct MemoryEntry
	{
		explicit MemoryEntry(void* address = nullptr, size_t count = 0)
			: _address(address), _capacity(count)
		{
		}
		void*	_address;
		size_t	_capacity;
	};

	namespace KETrait
	{
		DEFINE_TEMPLATE_BOOL_METHOD_TRAIT(HasAllocate, allocate);
		DEFINE_METHOD_TRAIT(HasDeallocate, deallocate);

		template<typename Allocator>
		struct AllocatorTrait : TraitCondition<
			SatisfyAll<
				KETrait::IsClass<Allocator>::value,
				CHECK_METHOD_TRAIT(HasAllocate, Allocator, MemoryEntry, const size_t),
				CHECK_METHOD_TRAIT(HasDeallocate, Allocator, void, MemoryEntry&)
			>::value, TrueTrait, FalseTrait>::Type
		{
		};
	};

}