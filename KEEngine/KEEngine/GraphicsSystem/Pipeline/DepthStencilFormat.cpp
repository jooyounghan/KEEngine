#include "GraphicsSystemPch.h"
#include "DepthStencilFormat.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthStencilFormat)
		DEFINE_REFLECT_ENUM_PROPERTY(DepthStencilFormat, _dsvFormat)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthStencilFormat)
		BIND_REFLECET_POD_PROPERTY(DepthStencilFormat, EDxgiFormat, _dsvFormat, EReflectUIOption::Editable, EDxgiFormat::Unknown);
	END_BIND_REFLECT_PROPERTY()
}
