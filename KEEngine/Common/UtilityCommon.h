#pragma once
#include <cassert>
#include <new>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <immintrin.h>

#pragma region Utility Macros
// =======================================================================================
#if _HAS_CXX17
#define CONSTEXPR_INLINE inline
#define NODISC					[[nodiscard]]
#define NODISC_MSG(warnMessage)	[[nodiscard(warnMessage)]]
#else
#define CONSTEXPR_INLINE
#define NODISC
#define NODISC_MSG(warnMessage)
#endif

#if _HAS_CXX20
#define NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#endif


#define KE_IN
#define KE_OUT
#define KE_INOUT

#ifdef _DEBUG																
#define DEBUG_ASSERT(expression, msg) if (expression == false) assert(msg)	
#else																		
#define DEBUG_ASSERT(expression, msg) ((void)0)
#endif																		

#define DEFAULT_DELETE_COPYABLE(ClassName)				\
	ClassName(const ClassName&) = delete;				\
	ClassName& operator=(const ClassName&) = delete;	

#define DEFAULT_DELETE_MOVEABLE(ClassName)				\
	ClassName(ClassName&&) = delete;					\
	ClassName& operator=(ClassName&&) = delete;

#define NONCOPYABLE(ClassName)							\
	DEFAULT_DELETE_COPYABLE(ClassName)					\
	DEFAULT_DELETE_MOVEABLE(ClassName)

#define DELETE_CONSTRUCTOR(ClassName)					\
	ClassName() = delete;								\
	NONCOPYABLE(ClassName)

#define DEFAULT_COPYABLE(ClassName)						\
	ClassName(const ClassName&) = default;				\
	ClassName& operator=(const ClassName&) = default;

#define DEFAULT_MOVEABLE(ClassName)						\
	ClassName(ClassName&&) = default;					\
	ClassName& operator=(ClassName&&) = default;

#define DEFAULTABLE(ClassName)							\
	DEFAULT_COPYABLE(ClassName)							\
	DEFAULT_MOVEABLE(ClassName)

#define DEFAULT_CONSTRUCTOR(ClassName)					\
	ClassName() = default;								\
	DEFAULTABLE(ClassName)


#define GET_BUFFER_PTR_AT(PtrType, Buffer, ColumnIndex) reinterpret_cast<PtrType*>(&Buffer[sizeof(PtrType) * ColumnIndex])

// =======================================================================================
#pragma endregion


namespace ke 
{
	using nullptr_t = decltype(nullptr);

	template<typename T>
	struct RemoveReference { using Type = T; };

	template<typename T>
	struct RemoveReference<T&> { using Type = T; };

	template<typename T>
	struct RemoveReference<T&&> { using Type = T; };

	template<typename T>
	inline typename RemoveReference<T>::Type&& move(T&& value) 
	{
		return static_cast<typename RemoveReference<T>::Type&&>(value);
	}

	template<typename T> struct IsLvalueReference { static constexpr bool value = false; };
	template<typename T> struct IsLvalueReference<T&> { static constexpr bool value = true; };

	template<typename T>
	inline constexpr T&& forward(typename RemoveReference<T>::Type& t) noexcept
	{
		return static_cast<T&&>(t);
	}

	template<typename T>
	inline constexpr T&& forward(typename RemoveReference<T>::Type&& t) noexcept
	{
		static_assert(!IsLvalueReference<T>::value, "bad forward of rvalue as lvalue");
		return static_cast<T&&>(t);
	}
}