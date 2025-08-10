#pragma once
#include "TypeTraits.h"
#include "StringHelper.h"
#include "MallocAllocator.h"

namespace ke
{
	template<typename CharType, typename Alloc = MallocAllocator<CharType>>
	class OwnedString
	{
	public:
		OwnedString(const CharType* str);
		OwnedString(const OwnedString& staticString);
		OwnedString(OwnedString&& staticString);
		~OwnedString();

	public:
		operator const CharType* () const = delete;
		operator const CharType* () = delete;
		operator CharType* () const = delete;
		operator CharType* () = delete;

	public:
		const CharType* c_str() const&;
		const CharType* c_str() const&& = delete;

	public:
		void append(const CharType* const str);
		void append(const OwnedString& staticString);

	public:
		size_t length() const { return _memoryEntry._capacity - 1; }
		size_t capacity() const { return _memoryEntry._capacity; }

	protected:
		NO_UNIQUE_ADDRESS Alloc _allocator;
		MemoryEntry				_memoryEntry;


#ifdef _DEBUG
	private:
		size_t			_length = 0;
		const CharType* _stringValuePtr;
#endif

		// Static Asserts
		static_assert(KETrait::AllocatorTrait<Alloc>::value, "Alloc does not satisfy the required AllocatorTrait.");
		static_assert(KETrait::IsCharacter<CharType>::value, "CharType only accept char, wchar_t");
	};

	using OwnedStringA = OwnedString<char>;
	using OwnedStringW = OwnedString<wchar_t>;
}

#include "OwnedString.hpp"