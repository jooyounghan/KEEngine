#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(RasterizerState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(RasterizerState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _fillMode, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _cullMode, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _frontCounterClockwise, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int32, _depthBias, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _depthBiasClamp, 0.f);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _slopeScaledDepthBias, 0.f);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthClipEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _multisampleEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _antialiasedLineEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _forcedSampleCount, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _conservativeRaster, 0);
	};
}
