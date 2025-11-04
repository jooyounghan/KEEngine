#pragma once
#include "UtilityCommon.h"
#include <cstdio>

#define HANDLE_ASSERTION_IF_FAILURE(condition, message)																				\
	if (!(condition))																												\
	{																																\
		fprintf(stderr, "Assertion failed: (%s), message: %s, file: %s, line: %d\n", #condition, (message), __FILE__, __LINE__);	\
		abort();																													\
	}

#define KE_ASSERT(condition, message) HANDLE_ASSERTION_IF_FAILURE(condition, message)

#ifdef _DEBUG
#define KE_DEBUG_ASSERT(condition, message)	KE_ASSERT(condition, message)
#else
#define KE_DEBUG_ASSERT(condition, message)	__noop
#endif // _DEBUG