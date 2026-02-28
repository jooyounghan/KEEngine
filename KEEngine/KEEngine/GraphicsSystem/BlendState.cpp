#include "GraphicsSystemPch.h"
#include "BlendState.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(BlendState)
		KE_DEFINE_REFLECT_POD_PROPERTY(BlendState, _alphaToCoverageEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(BlendState, _independentBlendEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(BlendState, _blendEnable)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _srcBlend)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _destBlend)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _blendOp)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _srcBlendAlpha)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _destBlendAlpha)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _blendOpAlpha)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(BlendState, _renderTargetWriteMask)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(BlendState)
		KE_BIND_REFLECT_POD_PROPERTY(BlendState, bool, _alphaToCoverageEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECT_POD_PROPERTY(BlendState, bool, _independentBlendEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECT_POD_PROPERTY(BlendState, bool, _blendEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlend, _srcBlend, EReflectUIOption::Editable, EBlend::One);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlend, _destBlend, EReflectUIOption::Editable, EBlend::Zero);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlendOp, _blendOp, EReflectUIOption::Editable, EBlendOp::Add);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlend, _srcBlendAlpha, EReflectUIOption::Editable, EBlend::One);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlend, _destBlendAlpha, EReflectUIOption::Editable, EBlend::Zero);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlendOp, _blendOpAlpha, EReflectUIOption::Editable, EBlendOp::Add);
		KE_BIND_REFLECT_ENUM_PROPERTY(BlendState, EBlendColorMask, _renderTargetWriteMask, EReflectUIOption::Editable, EBlendColorMask::Red | EBlendColorMask::Green | EBlendColorMask::Blue | EBlendColorMask::Alpha);
	KE_END_BIND_REFLECT_PROPERTY()
}
