#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(StencilState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(StencilState);

	public:
		DECLARE_REFLECT_PROPERTY(bool, _stencilEnable);
		DECLARE_REFLECT_PROPERTY(uint8, _stencilReadMask);
		DECLARE_REFLECT_PROPERTY(uint8, _stencilWriteMask);
		DECLARE_REFLECT_PROPERTY(uint8, _frontFaceStencilFailOp);
		DECLARE_REFLECT_PROPERTY(uint8, _frontFaceStencilDepthFailOp);
		DECLARE_REFLECT_PROPERTY(uint8, _frontFaceStencilPassOp);
		DECLARE_REFLECT_PROPERTY(uint8, _frontFaceStencilFunc);
		DECLARE_REFLECT_PROPERTY(uint8, _backFaceStencilFailOp);
		DECLARE_REFLECT_PROPERTY(uint8, _backFaceStencilDepthFailOp);
		DECLARE_REFLECT_PROPERTY(uint8, _backFaceStencilPassOp);
		DECLARE_REFLECT_PROPERTY(uint8, _backFaceStencilFunc);
	};
}
