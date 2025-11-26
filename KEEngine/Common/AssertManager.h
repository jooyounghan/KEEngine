#pragma once
#include "UtilityCommon.h"
#include <cstdio>

#define HANDLE_ASSERTION_IF_FAILURE(condition, message)																					\
	if (!(condition))																													\
	{																																	\
		fprintf(stderr, "Assertion failed: (%s), message: %s, file: %s, line: %d\n", #condition, (message), __FILE__, (int)__LINE__);	\
		abort();																														\
	}

#define HANDLE_ASSERTION_IF_FAILURE_FMT(condition, format, ...)																					\
	if (!(condition))																															\
	{																																			\
		fprintf(stderr, "Assertion failed: (%s), message: " format ", file: %s, line: %d\n", #condition, __VA_ARGS__, __FILE__, (int)__LINE__);	\
		abort();																																\
	}

#define KE_ASSERT(condition, message)			HANDLE_ASSERTION_IF_FAILURE(condition, message)
#define KE_ASSERT_ARGS(condition, format, ...)	HANDLE_ASSERTION_IF_FAILURE_FMT(condition, format, __VA_ARGS__)

#ifdef _DEBUG
#define KE_DEBUG_ASSERT(condition, message)				KE_ASSERT(condition, message)
#define KE_DEBUG_ASSERT_ARGS(condition, format, ...)	KE_ASSERT_ARRGS(condition, format, __VA_ARGS__)
#else
#define KE_DEBUG_ASSERT(condition, message)				__noop
#define KE_DEBUG_ASSERT_ARGS(condition, format, ...)	__noop
#endif // _DEBUG