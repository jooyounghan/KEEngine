#include "GraphicsSystemPch.h"
#include "PrimitiveTopology.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(PrimitiveTopology)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(PrimitiveTopology, _primitiveTopologyType)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(PrimitiveTopology)
		KE_BIND_REFLECT_POD_PROPERTY(PrimitiveTopology, EPrimitiveTopologyType, _primitiveTopologyType, EReflectUIOption::Editable, EPrimitiveTopologyType::Triangle);
	KE_END_BIND_REFLECT_PROPERTY()
}
