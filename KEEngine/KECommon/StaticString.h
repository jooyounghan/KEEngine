#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"
#include "MallocAllocator.h"

namespace ke
{
	template<typename CharType, typename Alloc = MallocAllocator<CharType>>
	class StaticString
	{
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");

	public:
		explicit StaticString(const CharType* str);
		~StaticString();

	public:
		operator const CharType* () const = delete;
		operator const CharType* () = delete;
		operator CharType* () const = delete;
		operator CharType* () = delete;

	public:
		const CharType* c_str() const&;
		const CharType* c_str() const&& = delete;

	protected:
		NO_UNIQUE_ADDRESS Alloc _allocator;
		MemoryEntry _memoryEntry;


#ifdef _DEBUG
	private:
		size_t _length;
		const CharType* _stringValuePtr;
#endif
	};

	using StaticStringA = StaticString<char>;
	using StaticStringW = StaticString<wchar_t>;
}

#include "StaticString.hpp"