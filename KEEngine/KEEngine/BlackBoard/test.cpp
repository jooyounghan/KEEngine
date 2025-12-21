#include "test.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(TestObject)
		DEFINE_REFLECT_PROPERTY(TestObject, int32, Health, 100, "Health of the object");
		DEFINE_REFLECT_PROPERTY(TestObject, float, Speed, 10.0f, "Speed of the object");
	END_DEFINE_REFLECT_PROPERTY(TestObject)
}