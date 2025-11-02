#include "AssertManager.h"
#include <cstdio>

namespace ke
{
	AssertManager& ke::AssertManager::getInstance()
	{
		static AssertManager instance;
		return instance;
	}

	void handleAssertionFailureIfFalse(bool condition, const char* conditionStr, const char* message, const char* file, int line)
	{
		if (!condition)
		{
			handleAssertionFailure(conditionStr, message, file, line);
		}
	}

	void handleAssertionFailure(const char* conditionStr, const char* message, const char* file, int line)
	{		
		fprintf(stderr, "Assertion failed: (%s), message: %s, file: %s, line: %d\n", conditionStr, message, file, line);
		abort();
	}
}
