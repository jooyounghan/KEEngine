#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(PrimitiveTopology)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(PrimitiveTopology);

	public:
		DECLARE_REFLECT_PROPERTY(EPrimitiveTopologyType, _primitiveTopologyType);
	};
}
