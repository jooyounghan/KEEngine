#include "GraphicsSystemPch.h"
#include "BlendState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(BlendState)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _alphaToCoverageEnable)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _independentBlendEnable)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _blendEnable)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _srcBlend)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _destBlend)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _blendOp)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _srcBlendAlpha)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _destBlendAlpha)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _blendOpAlpha)
		DEFINE_REFLECT_POD_PROPERTY(BlendState, _renderTargetWriteMask)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(BlendState)
		BIND_REFLECET_POD_PROPERTY(BlendState, bool, _alphaToCoverageEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_PROPERTY(BlendState, bool, _independentBlendEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_PROPERTY(BlendState, bool, _blendEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _srcBlend, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _destBlend, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _blendOp, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _srcBlendAlpha, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _destBlendAlpha, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _blendOpAlpha, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(BlendState, uint8, _renderTargetWriteMask, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
