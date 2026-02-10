#include "GraphicsSystemPch.h"
#include "DepthStencilFormat.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DepthStencilFormat)
		DEFINE_REFLECT_PROPERTY(DepthStencilFormat, uint8, _dsvFormat)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DepthStencilFormat)
		BIND_REFLECT_PROPERTY(DepthStencilFormat, uint8, _dsvFormat, EReflectUIOption::Editable, 0, 255, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
