#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(RenderTargetFormats)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(RenderTargetFormats);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _numRenderTargets, 0);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat0);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat1);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat2);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat3);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat4);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat5);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat6);
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat7);
	};
}
