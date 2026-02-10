#include "GraphicsSystemPch.h"
#include "PrimitiveTopology.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(PrimitiveTopology)
		DEFINE_REFLECT_PROPERTY(PrimitiveTopology, uint8, _primitiveTopologyType)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(PrimitiveTopology)
		BIND_REFLECT_PROPERTY(PrimitiveTopology, uint8, _primitiveTopologyType, EReflectUIOption::Editable, 0, 5, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
