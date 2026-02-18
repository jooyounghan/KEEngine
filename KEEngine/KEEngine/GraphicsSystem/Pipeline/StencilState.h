#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(StencilState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(StencilState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _stencilEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilReadMask, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilWriteMask, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _frontFaceStencilFailOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _frontFaceStencilDepthFailOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _frontFaceStencilPassOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _frontFaceStencilFunc, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _backFaceStencilFailOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _backFaceStencilDepthFailOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _backFaceStencilPassOp, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _backFaceStencilFunc, 0);
	};
}
