#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(DepthStencilFormat)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(DepthStencilFormat);

	public:
		KE_DECLARE_REFLECT_PROPERTY(EDxgiFormat, _dsvFormat);
	};
}
