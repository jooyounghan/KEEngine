#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(DepthState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(DepthState);

	public:
		DECLARE_REFLECT_PROPERTY(bool, _depthEnable);
		DECLARE_REFLECT_PROPERTY(uint8, _depthWriteMask);
		DECLARE_REFLECT_PROPERTY(uint8, _depthFunc);
	};
}
