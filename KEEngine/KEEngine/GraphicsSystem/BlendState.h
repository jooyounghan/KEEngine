#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(BlendState)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(BlendState);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _alphaToCoverageEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _independentBlendEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _blendEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _srcBlend, EBlend::One);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _destBlend, EBlend::Zero);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendOp, _blendOp, EBlendOp::Add);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _srcBlendAlpha, EBlend::One);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlend, _destBlendAlpha, EBlend::Zero);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendOp, _blendOpAlpha, EBlendOp::Add);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EBlendColorMask, _renderTargetWriteMask, EBlendColorMask::Red | EBlendColorMask::Green | EBlendColorMask::Blue | EBlendColorMask::Alpha);
	};
}
