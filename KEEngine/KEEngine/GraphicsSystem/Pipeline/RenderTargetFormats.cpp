#include "GraphicsSystemPch.h"
#include "RenderTargetFormats.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(RenderTargetFormats)
		DEFINE_REFLECT_POD_PROPERTY(RenderTargetFormats, _numRenderTargets)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat0)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat1)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat2)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat3)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat4)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat5)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat6)
		DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat7)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(RenderTargetFormats)
		BIND_REFLECET_POD_RANGED_PROPERTY(RenderTargetFormats, uint8, _numRenderTargets, EReflectUIOption::Editable, 0, 8, 1, 0);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat0, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat1, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat2, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat3, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat4, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat5, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat6, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_PROPERTY(RenderTargetFormats, EDxgiFormat, _rtvFormat7, EReflectUIOption::Editable, EDxgiFormat::Unknown);
	END_BIND_REFLECT_PROPERTY()
}
