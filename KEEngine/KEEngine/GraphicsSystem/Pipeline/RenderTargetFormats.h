#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(RenderTargetFormats)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(RenderTargetFormats);

	public:
		DECLARE_REFLECT_PROPERTY(uint8, _numRenderTargets);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat0);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat1);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat2);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat3);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat4);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat5);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat6);
		DECLARE_REFLECT_PROPERTY(uint8, _rtvFormat7);
	};
}
