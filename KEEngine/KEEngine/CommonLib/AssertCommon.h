#pragma once
#include "CommonLibPch.h"

// Assertion ============================================================================
#define HANDLE_IF_FAILURE(method, condition, message)																					\
	if (!(condition))																													\
	{																																	\
		fprintf(stderr, "Assertion failed: (%s), message: %s, file: %s, line: %d\n", #condition, (message), __FILE__, (int)__LINE__);	\
		method;																														\
	}

#define HANDLE_IF_FAILURE_FMT(method, condition, format, ...)																					\
	if (!(condition))																															\
	{																																			\
		fprintf(stderr, "Assertion failed: (%s), message: " format ", file: %s, line: %d\n", #condition, __VA_ARGS__, __FILE__, (int)__LINE__);	\
		method;																																\
	}

#define KE_ASSERT(condition, message)			HANDLE_IF_FAILURE(abort(), condition, message)
#define KE_ASSERT_ARGS(condition, format, ...)	HANDLE_IF_FAILURE_FMT(abort(), condition, format, __VA_ARGS__)

#ifdef _DEBUG
#define KE_DEBUG_ASSERT(condition, message)				KE_ASSERT(condition, message)
#define KE_DEBUG_ASSERT_ARGS(condition, format, ...)	KE_ASSERT_ARGS(condition, format, __VA_ARGS__)
#else
#define KE_DEBUG_ASSERT(condition, message)				__noop
#define KE_DEBUG_ASSERT_ARGS(condition, format, ...)	__noop
#endif // _DEBUG

#define KE_RETURN(condition, message)			HANDLE_IF_FAILURE(return, condition, message)
#define KE_RETURN_ARGS(condition, format, ...)	HANDLE_IF_FAILURE(return, condition, format, __VA_ARGS__)

#ifdef _DEBUG
#define KE_DEBUG_RETURN(condition, message)				KE_RETURN(condition, message)
#define KE_DEBUG_RETURN_ARGS(condition, format, ...)	KE_RETURN_ARGS(condition, format, __VA_ARGS__)
#else
#define KE_DEBUG_RETURN(condition, message)			__noop
#define KE_DEBUG_RETURN_ARGS(condition, format, ...)	__noop
#endif // _DEBUG


#if defined(__clang__)
#define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(__GNUC__)
#define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define FUNC_NAME __FUNCSIG__
#else
#define FUNC_NAME __func__
#endif

// Specialization ============================================================================
#define STATIC_ASSERT(condition, message)	\
	static_assert(condition,				\
		message								\
	)
#define STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ClassName)	\
	static_assert(false,								\
		#ClassName										\
		" does not support for this template type."		\
		" Triggered in: " FUNC_NAME						\
	)