#pragma once
#include "ReflectObject.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(SampleMask)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(SampleMask);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _sampleMask, 0);
	};
}
