#include "GraphicsSystemPch.h"
#include "DepthState.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(DepthState)
		KE_DEFINE_REFLECT_POD_PROPERTY(DepthState, _depthEnable)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(DepthState, _depthWriteMask)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(DepthState, _depthFunc)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(DepthState)
		KE_BIND_REFLECT_POD_PROPERTY(DepthState, bool, _depthEnable, EReflectUIOption::Editable, true);
		KE_BIND_REFLECT_POD_PROPERTY(DepthState, EDepthWriteMask, _depthWriteMask, EReflectUIOption::Editable, EDepthWriteMask::All);
		KE_BIND_REFLECT_POD_PROPERTY(DepthState, EComparisonFunc, _depthFunc, EReflectUIOption::Editable, EComparisonFunc::Less);
	KE_END_BIND_REFLECT_PROPERTY()
}
