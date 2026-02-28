#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(PrimitiveTopology)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(PrimitiveTopology);

	public:
		KE_DECLARE_REFLECT_PROPERTY(EPrimitiveTopologyType, _primitiveTopologyType);
	};
}
