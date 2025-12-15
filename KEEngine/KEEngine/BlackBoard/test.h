#pragma once
#include "ReflectObject.h"
#include "ReflectProperty.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(TestObject)
	{
	public:
		TestObject() : REFLECT_OBJECT_CONSTRUCTOR() {}
		DECLARE_REFLECT_PROPERTY(int32, Health);
		DECLARE_REFLECT_PROPERTY(float, Speed);
	};
}