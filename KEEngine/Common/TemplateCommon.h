#pragma once

#if defined(__clang__)
#define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(__GNUC__)
#define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define FUNC_NAME __FUNCSIG__
#else
#define FUNC_NAME __func__
#endif

// Specialization
#define STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ClassName)	\
	static_assert(false,								\
		#ClassName										\
		" does not support for this template type."		\
		" Triggered in: " FUNC_NAME						\
	)