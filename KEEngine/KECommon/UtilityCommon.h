#pragma once

#define NODISC					[[nodiscard]]
#define NODISC_MSG(warnMessage)	[[nodiscard(warnMessage)]]

#if _HAS_CXX17
#define KE_INLINE inline
#else
#define CONSTEXPR_INLINE
#endif

#define KE_IN
#define KE_OUT

#define DELETE_CONSTRUCTOR(ClassName)					\
	ClassName() = delete;								\
	ClassName(const ClassName&) = delete;				\
	ClassName(ClassName&&) = delete;					\
	ClassName& operator=(const ClassName&) = delete;	\
	ClassName& operator=(ClassName&&) = delete;