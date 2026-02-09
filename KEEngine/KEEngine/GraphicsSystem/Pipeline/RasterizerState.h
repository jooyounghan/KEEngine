#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(RasterizerState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(RasterizerState);

	public:
		DECLARE_REFLECT_PROPERTY(uint8, _fillMode);
		DECLARE_REFLECT_PROPERTY(uint8, _cullMode);
		DECLARE_REFLECT_PROPERTY(bool, _frontCounterClockwise);
		DECLARE_REFLECT_PROPERTY(int32, _depthBias);
		DECLARE_REFLECT_PROPERTY(float, _depthBiasClamp);
		DECLARE_REFLECT_PROPERTY(float, _slopeScaledDepthBias);
		DECLARE_REFLECT_PROPERTY(bool, _depthClipEnable);
		DECLARE_REFLECT_PROPERTY(bool, _multisampleEnable);
		DECLARE_REFLECT_PROPERTY(bool, _antialiasedLineEnable);
		DECLARE_REFLECT_PROPERTY(uint32, _forcedSampleCount);
		DECLARE_REFLECT_PROPERTY(uint8, _conservativeRaster);
	};
}
