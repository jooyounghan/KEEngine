#include "GraphicsSystemPch.h"
#include "PrimitiveTopology.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(PrimitiveTopology)
		DEFINE_REFLECT_ENUM_PROPERTY(PrimitiveTopology, _primitiveTopologyType)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(PrimitiveTopology)
		BIND_REFLECET_POD_PROPERTY(PrimitiveTopology, EPrimitiveTopologyType, _primitiveTopologyType, EReflectUIOption::Editable, EPrimitiveTopologyType::Triangle);
	END_BIND_REFLECT_PROPERTY()
}
