#include "GraphicsSystemPch.h"
#include "RasterizerState.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(RasterizerState)
		DEFINE_REFLECT_PROPERTY(RasterizerState, uint8, _fillMode)
		DEFINE_REFLECT_PROPERTY(RasterizerState, uint8, _cullMode)
		DEFINE_REFLECT_PROPERTY(RasterizerState, bool, _frontCounterClockwise)
		DEFINE_REFLECT_PROPERTY(RasterizerState, int32, _depthBias)
		DEFINE_REFLECT_PROPERTY(RasterizerState, float, _depthBiasClamp)
		DEFINE_REFLECT_PROPERTY(RasterizerState, float, _slopeScaledDepthBias)
		DEFINE_REFLECT_PROPERTY(RasterizerState, bool, _depthClipEnable)
		DEFINE_REFLECT_PROPERTY(RasterizerState, bool, _multisampleEnable)
		DEFINE_REFLECT_PROPERTY(RasterizerState, bool, _antialiasedLineEnable)
		DEFINE_REFLECT_PROPERTY(RasterizerState, uint32, _forcedSampleCount)
		DEFINE_REFLECT_PROPERTY(RasterizerState, uint8, _conservativeRaster)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(RasterizerState)
		BIND_REFLECT_PROPERTY(RasterizerState, uint8, _fillMode, EReflectUIOption::Editable, 0, 3, 1, 0);
		BIND_REFLECT_PROPERTY(RasterizerState, uint8, _cullMode, EReflectUIOption::Editable, 0, 3, 1, 0);
		BIND_REFLECT_PROPERTY(RasterizerState, bool, _frontCounterClockwise, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(RasterizerState, int32, _depthBias, EReflectUIOption::Editable, -10000, 10000, 1, 0);
		BIND_REFLECT_PROPERTY(RasterizerState, float, _depthBiasClamp, EReflectUIOption::Editable, -1.0f, 1.0f, 0.01f, 0.0f);
		BIND_REFLECT_PROPERTY(RasterizerState, float, _slopeScaledDepthBias, EReflectUIOption::Editable, -10.0f, 10.0f, 0.1f, 0.0f);
		BIND_REFLECT_PROPERTY(RasterizerState, bool, _depthClipEnable, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(RasterizerState, bool, _multisampleEnable, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(RasterizerState, bool, _antialiasedLineEnable, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(RasterizerState, uint32, _forcedSampleCount, EReflectUIOption::Editable, 0, 16, 1, 0);
		BIND_REFLECT_PROPERTY(RasterizerState, uint8, _conservativeRaster, EReflectUIOption::Editable, 0, 1, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
