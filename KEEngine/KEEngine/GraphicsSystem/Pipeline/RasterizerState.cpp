#include "GraphicsSystemPch.h"
#include "RasterizerState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(RasterizerState)
		DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _fillMode)
		DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _cullMode)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _frontCounterClockwise)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthBias)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthBiasClamp)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _slopeScaledDepthBias)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _depthClipEnable)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _multisampleEnable)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _antialiasedLineEnable)
		DEFINE_REFLECT_POD_PROPERTY(RasterizerState, _forcedSampleCount)
		DEFINE_REFLECT_ENUM_PROPERTY(RasterizerState, _conservativeRaster)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(RasterizerState)
		BIND_REFLECET_POD_PROPERTY(RasterizerState, EFillMode, _fillMode, EReflectUIOption::Editable, EFillMode::Solid);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, ECullMode, _cullMode, EReflectUIOption::Editable, ECullMode::Back);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, bool, _frontCounterClockwise, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, int32, _depthBias, EReflectUIOption::Editable, -10000, 10000, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, float, _depthBiasClamp, EReflectUIOption::Editable, -1.0f, 1.0f, 0.01f, 0.0f);
		BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, float, _slopeScaledDepthBias, EReflectUIOption::Editable, -10.0f, 10.0f, 0.1f, 0.0f);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, bool, _depthClipEnable, EReflectUIOption::Editable, true);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, bool, _multisampleEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, bool, _antialiasedLineEnable, EReflectUIOption::Editable, false);
		BIND_REFLECET_POD_RANGED_PROPERTY(RasterizerState, uint32, _forcedSampleCount, EReflectUIOption::Editable, 0, 16, 1, 0);
		BIND_REFLECET_POD_PROPERTY(RasterizerState, EConservativeRasterizationMode, _conservativeRaster, EReflectUIOption::Editable, EConservativeRasterizationMode::Off);
	END_BIND_REFLECT_PROPERTY()
}
