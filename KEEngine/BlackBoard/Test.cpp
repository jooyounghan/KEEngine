#include "Test.h"

BEGIN_DEFINE_REFLECT_PROPERTY(Test);
	DEFINE_REFLECT_PROPERTY(Test, bool, TestBool, false, "테스트용");
	DEFINE_REFLECT_PROPERTY(Test, float, MinValue, 0.3f, "최소값");
	DEFINE_REFLECT_PROPERTY(Test, float, MaxValue, 0.5f, "최대값");
END_DEFINE_REFLECT_PROPERTY(Test);
