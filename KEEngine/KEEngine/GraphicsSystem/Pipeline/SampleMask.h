#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(SampleMask)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(SampleMask);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _sampleMask, 0);
	};
}
