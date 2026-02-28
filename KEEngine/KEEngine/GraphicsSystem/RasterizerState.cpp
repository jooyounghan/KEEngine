#include "GraphicsSystemPch.h"
#include "RasterizerState.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(RasterizerState)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _fillMode)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _cullMode)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _frontCounterClockwise)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthBias)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthBiasClamp)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _slopeScaledDepthBias)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthClipEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _multisampleEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _antialiasedLineEnable)
		KE_DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _forcedSampleCount)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _conservativeRaster)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(RasterizerState)
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, EFillMode, _fillMode, EReflectUIOption::Editable, EFillMode::Solid);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, ECullMode, _cullMode, EReflectUIOption::Editable, ECullMode::Back);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, bool, _frontCounterClockwise, EReflectUIOption::Editable, false);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, int32, _depthBias, EReflectUIOption::Editable, -10000, 10000, 1, 0);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, float, _depthBiasClamp, EReflectUIOption::Editable, -1.0f, 1.0f, 0.01f, 0.0f);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, float, _slopeScaledDepthBias, EReflectUIOption::Editable, -10.0f, 10.0f, 0.1f, 0.0f);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, bool, _depthClipEnable, EReflectUIOption::Editable, true);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, bool, _multisampleEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, bool, _antialiasedLineEnable, EReflectUIOption::Editable, false);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, uint32, _forcedSampleCount, EReflectUIOption::Editable, 0, 16, 1, 0);
		KE_BIND_REFLECT_POD_PROPERTY(RasterizerState, EConservativeRasterizationMode, _conservativeRaster, EReflectUIOption::Editable, EConservativeRasterizationMode::Off);
	KE_END_BIND_REFLECT_PROPERTY()
}
