#pragma once
#include "UtilityCommon.h"

namespace ke
{
	class AssertManager
	{
	private:
		AssertManager() = default;
		~AssertManager() = default;
		NONCOPYABLE(AssertManager);

	public:
		static AssertManager& getInstance();

	public:
		void handleAssertionFailure(const char* conditionStr, const char* message, const char* file, int line);
		void handleAssertionFailureIfFalse(bool condition, const char* conditionStr, const char* message, const char* file, int line);
	};
}


#ifdef _DEBUG
#define KE_DEBUG_ASSERT(condition, message)																	\
	AssertManager& assertManager = ke::AssertManager::getInstance();										\
	assertManager.handleAssertionFailureIfFalse((condition), #condition, (message), __FILE__, __LINE__);
#else
#define KE_DEBUG_ASSERT(condition, message)	__noop
#endif // _DEBUG

#define KE_ASSERT(condition, message)																		\
	AssertManager& assertManager = ke::AssertManager::getInstance();										\
	assertManager.handleAssertionFailureIfFalse((condition), #condition, (message), __FILE__, __LINE__);