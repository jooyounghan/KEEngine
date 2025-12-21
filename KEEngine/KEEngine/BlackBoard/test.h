#pragma once
#include "ReflectObject.h"
#include "ReflectProperty.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(TestObject)
	{
	public:
		TestObject() : REFLECT_OBJECT_CONSTRUCTOR(TestObject) {}

	BEGIN_DECLARE_REFLECT_PROPERTY(TestObject)
		DECLARE_REFLECT_PROPERTY(int32, Health);
		DECLARE_REFLECT_PROPERTY(float, Speed);
	END_DECLARE_REFLECT_PROPERTY();
	};
}