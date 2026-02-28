#include "GraphicsSystemPch.h"
#include "RenderTargetFormats.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(RenderTargetFormats)
		KE_DEFINE_REFLECT_POD_PROPERTY(RenderTargetFormats, _numRenderTargets)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat0)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat1)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat2)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat3)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat4)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat5)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat6)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(RenderTargetFormats, _rtvFormat7)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(RenderTargetFormats)
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(RenderTargetFormats, uint8, _numRenderTargets, EReflectUIOption::Editable, 0, 8, 1, 0);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat0, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat1, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat2, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat3, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat4, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat5, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat6, EReflectUIOption::Editable, EDXGIFormat::Unknown);
		KE_BIND_REFLECT_POD_PROPERTY(RenderTargetFormats, EDXGIFormat, _rtvFormat7, EReflectUIOption::Editable, EDXGIFormat::Unknown);
	KE_END_BIND_REFLECT_PROPERTY()
}
