#pragma once
#include "ReflectObject.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(SampleDesc)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(SampleDesc);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _count, 0);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _quality, 0);
	};
}
