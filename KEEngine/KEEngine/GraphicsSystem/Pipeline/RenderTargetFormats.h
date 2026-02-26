#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(RenderTargetFormats)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(RenderTargetFormats);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _numRenderTargets, 0);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat0);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat1);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat2);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat3);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat4);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat5);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat6);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _rtvFormat7);
	};
}
