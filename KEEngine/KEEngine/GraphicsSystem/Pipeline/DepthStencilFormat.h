#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(DepthStencilFormat)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(DepthStencilFormat);

	public:
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _dsvFormat);
	};
}
