#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(DepthState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(DepthState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _depthWriteMask, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _depthFunc, 0);
	};
}
