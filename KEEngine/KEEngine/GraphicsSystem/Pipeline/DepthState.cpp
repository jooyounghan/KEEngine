#include "GraphicsSystemPch.h"
#include "DepthState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthState)
		DEFINE_REFLECT_PROPERTY(DepthState, bool, _depthEnable)
		DEFINE_REFLECT_PROPERTY(DepthState, uint8, _depthWriteMask)
		DEFINE_REFLECT_PROPERTY(DepthState, uint8, _depthFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthState)
		BIND_REFLECT_PROPERTY(DepthState, bool, _depthEnable, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(DepthState, uint8, _depthWriteMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(DepthState, uint8, _depthFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
