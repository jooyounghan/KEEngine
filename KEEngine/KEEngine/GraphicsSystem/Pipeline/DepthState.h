#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(DepthState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(DepthState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthEnable, true);
		DECLARE_REFLECT_PROPERTY(EDepthWriteMask, _depthWriteMask);
		DECLARE_REFLECT_PROPERTY(EComparisonFunc, _depthFunc);
	};
}
