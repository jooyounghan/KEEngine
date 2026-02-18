#pragma once
#include "ReflectObject.h"

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
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _srcBlend, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _destBlend, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _blendOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _srcBlendAlpha, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _destBlendAlpha, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _blendOpAlpha, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _renderTargetWriteMask, 0);
	};
}
