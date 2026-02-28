#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(DepthState)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(DepthState);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthEnable, true);
		KE_DECLARE_REFLECT_PROPERTY(EDepthWriteMask, _depthWriteMask);
		KE_DECLARE_REFLECT_PROPERTY(EComparisonFunc, _depthFunc);
	};
}
