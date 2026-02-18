#include "GraphicsSystemPch.h"
#include "StencilState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(StencilState)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilEnable)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilReadMask)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _stencilWriteMask)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _frontFaceStencilFailOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _frontFaceStencilDepthFailOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _frontFaceStencilPassOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _frontFaceStencilFunc)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _backFaceStencilFailOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _backFaceStencilDepthFailOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _backFaceStencilPassOp)
		DEFINE_REFLECT_POD_PROPERTY(StencilState, _backFaceStencilFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(StencilState)
		BIND_REFLECET_POD_PROPERTY(StencilState, bool, _stencilEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilReadMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _stencilWriteMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _frontFaceStencilFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _frontFaceStencilDepthFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _frontFaceStencilPassOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _frontFaceStencilFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _backFaceStencilFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _backFaceStencilDepthFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _backFaceStencilPassOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(StencilState, uint8, _backFaceStencilFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
