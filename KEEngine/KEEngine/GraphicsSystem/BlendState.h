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
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _srcBlend, EBlend::One);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _destBlend, EBlend::Zero);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendOp, _blendOp, EBlendOp::Add);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _srcBlendAlpha, EBlend::One);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _destBlendAlpha, EBlend::Zero);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendOp, _blendOpAlpha, EBlendOp::Add);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendColorMask, _renderTargetWriteMask, EBlendColorMask::Red | EBlendColorMask::Green | EBlendColorMask::Blue | EBlendColorMask::Alpha);
	};
}
