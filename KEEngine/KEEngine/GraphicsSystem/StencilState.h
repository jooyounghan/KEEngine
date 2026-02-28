#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(StencilState)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(StencilState);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(bool, _stencilEnable, false);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilReadMask, 0xff);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilWriteMask, 0xff);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilFailOp);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilDepthFailOp);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _frontFaceStencilPassOp);
		KE_DECLARE_REFLECT_PROPERTY(EComparisonFunc, _frontFaceStencilFunc);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilFailOp);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilDepthFailOp);
		KE_DECLARE_REFLECT_PROPERTY(EStencilOp, _backFaceStencilPassOp);
		KE_DECLARE_REFLECT_PROPERTY(EComparisonFunc, _backFaceStencilFunc);
	};
}
