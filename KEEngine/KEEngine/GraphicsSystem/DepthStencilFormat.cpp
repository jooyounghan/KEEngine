#include "GraphicsSystemPch.h"
#include "DepthStencilFormat.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(DepthStencilFormat)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(DepthStencilFormat, _dsvFormat)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(DepthStencilFormat)
		KE_BIND_REFLECT_POD_PROPERTY(DepthStencilFormat, EDxgiFormat, _dsvFormat, EReflectUIOption::Editable, EDxgiFormat::Unknown);
	KE_END_BIND_REFLECT_PROPERTY()
}
