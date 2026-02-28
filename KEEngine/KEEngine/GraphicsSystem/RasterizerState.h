#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(RasterizerState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(RasterizerState);

	public:
		DECLARE_REFLECT_PROPERTY(EFillMode, _fillMode);
		DECLARE_REFLECT_PROPERTY(ECullMode, _cullMode);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _frontCounterClockwise, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int32, _depthBias, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _depthBiasClamp, 0.f);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _slopeScaledDepthBias, 0.f);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthClipEnable, true);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _multisampleEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _antialiasedLineEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _forcedSampleCount, 0);
		DECLARE_REFLECT_PROPERTY(EConservativeRasterizationMode, _conservativeRaster);
	};
}
