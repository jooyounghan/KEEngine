#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(RasterizerState)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(RasterizerState);

	public:
		KE_DECLARE_REFLECT_PROPERTY(EFillMode, _fillMode);
		KE_DECLARE_REFLECT_PROPERTY(ECullMode, _cullMode);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _frontCounterClockwise, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int32, _depthBias, 0);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _depthBiasClamp, 0.f);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _slopeScaledDepthBias, 0.f);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _depthClipEnable, true);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _multisampleEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _antialiasedLineEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _forcedSampleCount, 0);
		KE_DECLARE_REFLECT_PROPERTY(EConservativeRasterizationMode, _conservativeRaster);
	};
}
