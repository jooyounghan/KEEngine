#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(SampleDesc)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(SampleDesc);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _count, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _quality, 0);
	};
}
