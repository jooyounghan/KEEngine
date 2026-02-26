#include "GraphicsSystemPch.h"
#include "DepthState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthState)
		DEFINE_REFLECT_POD_PROPERTY(DepthState, _depthEnable)
		DEFINE_REFLECT_ENUM_PROPERTY(DepthState, _depthWriteMask)
		DEFINE_REFLECT_ENUM_PROPERTY(DepthState, _depthFunc)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthState)
		BIND_REFLECET_POD_PROPERTY(DepthState, bool, _depthEnable, EReflectUIOption::Editable, true);
		BIND_REFLECET_POD_PROPERTY(DepthState, EDepthWriteMask, _depthWriteMask, EReflectUIOption::Editable, EDepthWriteMask::All);
		BIND_REFLECET_POD_PROPERTY(DepthState, EComparisonFunc, _depthFunc, EReflectUIOption::Editable, EComparisonFunc::Less);
	END_BIND_REFLECT_PROPERTY()
}
