#pragma once
#include <cassert>

#pragma region Utility Macros
// =======================================================================================
#define NODISC					[[nodiscard]]
#define NODISC_MSG(warnMessage)	[[nodiscard(warnMessage)]]

#if _HAS_CXX17
#define CONSTEXPR_INLINE inline
#else
#define CONSTEXPR_INLINE
#endif

#define KE_IN
#define KE_OUT

#ifdef _DEBUG																
#define DEBUG_ASSERT(expression, msg) if (expression == false) assert(msg)	
#else																		
#define DEBUG_ASSERT(expression, msg) ((void)0)								
#endif																		

#define DELETE_CONSTRUCTOR(ClassName)					\
	ClassName() = delete;								\
	ClassName(const ClassName&) = delete;				\
	ClassName(ClassName&&) = delete;					\
	ClassName& operator=(const ClassName&) = delete;	\
	ClassName& operator=(ClassName&&) = delete;
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
	typename RemoveReference<T>::Type&& move(T&& value) 
	{
		return static_cast<typename RemoveReference<T>::Type&&>(value);
	}
}