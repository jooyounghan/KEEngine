#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(BlendState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(BlendState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _alphaToCoverageEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _independentBlendEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _blendEnable, false);
		DECLARE_REFLECT_PROPERTY(EBlend, _srcBlend);
		DECLARE_REFLECT_PROPERTY(EBlend, _destBlend);
		DECLARE_REFLECT_PROPERTY(EBlendOp, _blendOp);
		DECLARE_REFLECT_PROPERTY(EBlend, _srcBlendAlpha);
		DECLARE_REFLECT_PROPERTY(EBlend, _destBlendAlpha);
		DECLARE_REFLECT_PROPERTY(EBlendOp, _blendOpAlpha);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _renderTargetWriteMask, 15);
	};
}
