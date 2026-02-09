#include "GraphicsSystemPch.h"
#include "StencilState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(StencilState)
		DEFINE_REFLECT_PROPERTY(StencilState, bool, _stencilEnable)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _stencilReadMask)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _stencilWriteMask)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilFailOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilDepthFailOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilPassOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilFunc)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilFailOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilDepthFailOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilPassOp)
		DEFINE_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(StencilState)
		BIND_REFLECT_PROPERTY(StencilState, bool, _stencilEnable, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _stencilReadMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _stencilWriteMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilDepthFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilPassOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _frontFaceStencilFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilDepthFailOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilPassOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(StencilState, uint8, _backFaceStencilFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
