#include "GraphicsSystemPch.h"
#include "StencilState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(StencilState)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilEnable)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilReadMask)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilWriteMask)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilFailOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilDepthFailOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilPassOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _frontFaceStencilFunc)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilFailOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilDepthFailOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilPassOp)
		DEFINE_REFLECT_ENUM_PROPERTY(StencilState, _backFaceStencilFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(StencilState)
		BIND_REFLECET_POD_PROPERTY(StencilState, bool, _stencilEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilReadMask, EReflectUIOption::Editable, 0xff, 0xff, 0, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilWriteMask, EReflectUIOption::Editable, 0xff, 0xff, 0, 1);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilDepthFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _frontFaceStencilPassOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EComparisonFunc, _frontFaceStencilFunc, EReflectUIOption::Editable, EComparisonFunc::Always);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilDepthFailOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EStencilOp, _backFaceStencilPassOp, EReflectUIOption::Editable, EStencilOp::Keep);
		BIND_REFLECET_POD_PROPERTY(StencilState, EComparisonFunc, _backFaceStencilFunc, EReflectUIOption::Editable, EComparisonFunc::Always);
	END_BIND_REFLECT_PROPERTY()
}
