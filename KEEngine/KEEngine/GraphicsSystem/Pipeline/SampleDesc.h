#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(SampleDesc)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(SampleDesc);

	public:
		DECLARE_REFLECT_PROPERTY(uint32, _count);
		DECLARE_REFLECT_PROPERTY(uint32, _quality);
	};
}
