#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(StencilState)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(StencilState);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _stencilEnable, false);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilReadMask, 0xff);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilWriteMask, 0xff);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilFailOp);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilDepthFailOp);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilPassOp);
		DECLARE_REFLECT_PROPERTY(EComparisonFunc, _frontFaceStencilFunc);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilFailOp);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilDepthFailOp);
		DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilPassOp);
		DECLARE_REFLECT_PROPERTY(EComparisonFunc, _backFaceStencilFunc);
	};
}
