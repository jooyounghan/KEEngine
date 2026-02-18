#include "GraphicsSystemPch.h"
#include "DepthState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthState)
		DEFINE_REFLECT_POD_PROPERTY(DepthState, _depthEnable)
		DEFINE_REFLECT_POD_PROPERTY(DepthState, _depthWriteMask)
		DEFINE_REFLECT_POD_PROPERTY(DepthState, _depthFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthState)
		BIND_REFLECET_POD_PROPERTY(DepthState, bool, _depthEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(DepthState, uint8, _depthWriteMask, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(DepthState, uint8, _depthFunc, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
