#include "GraphicsSystemPch.h"
#include "StencilState.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(StencilState)
		KE_DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilReadMask)
		KE_DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilWriteMask)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilFailOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilDepthFailOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilPassOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilFunc)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilFailOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilDepthFailOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilPassOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilFunc)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(StencilState)
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, bool, _stencilEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilReadMask, EReflectUIOption::Editable, 0xff, 0xff, 0, 1);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilWriteMask, EReflectUIOption::Editable, 0xff, 0xff, 0, 1);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilDepthFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilPassOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EComparisonFunc, _frontFaceStencilFunc, EReflectUIOption::Editable, EComparisonFunc::Always);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilDepthFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilPassOp, EReflectUIOption::Editable, EStencilOp::Keep);
		KE_BIND_REFLECT_POD_PROPERTY(StencilState, EComparisonFunc, _backFaceStencilFunc, EReflectUIOption::Editable, EComparisonFunc::Always);
	KE_END_BIND_REFLECT_PROPERTY()
}
