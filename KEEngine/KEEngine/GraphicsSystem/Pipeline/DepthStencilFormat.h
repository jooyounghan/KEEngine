#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(DepthStencilFormat)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(DepthStencilFormat);

	public:
		DECLARE_REFLECT_PROPERTY(uint8, _dsvFormat);
	};
}
