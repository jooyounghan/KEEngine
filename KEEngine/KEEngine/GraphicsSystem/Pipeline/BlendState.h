#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(BlendState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(BlendState);

	public:
		DECLARE_REFLECT_PROPERTY(bool, _alphaToCoverageEnable);
		DECLARE_REFLECT_PROPERTY(bool, _independentBlendEnable);
		DECLARE_REFLECT_PROPERTY(bool, _blendEnable);
		DECLARE_REFLECT_PROPERTY(uint8, _srcBlend);
		DECLARE_REFLECT_PROPERTY(uint8, _destBlend);
		DECLARE_REFLECT_PROPERTY(uint8, _blendOp);
		DECLARE_REFLECT_PROPERTY(uint8, _srcBlendAlpha);
		DECLARE_REFLECT_PROPERTY(uint8, _destBlendAlpha);
		DECLARE_REFLECT_PROPERTY(uint8, _blendOpAlpha);
		DECLARE_REFLECT_PROPERTY(uint8, _renderTargetWriteMask);
	};
}
