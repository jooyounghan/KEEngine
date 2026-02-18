#include "GraphicsSystemPch.h"
#include "DepthStencilFormat.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthStencilFormat)
		DEFINE_REFLECT_POD_PROPERTY(DepthStencilFormat, _dsvFormat)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthStencilFormat)
		BIND_REFLECET_POD_RANGED_PROPERTY(DepthStencilFormat, uint8, _dsvFormat, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
