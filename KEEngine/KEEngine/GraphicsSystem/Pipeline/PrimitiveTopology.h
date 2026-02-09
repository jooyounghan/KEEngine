#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(PrimitiveTopology)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(PrimitiveTopology);

	public:
		DECLARE_REFLECT_PROPERTY(uint8, _primitiveTopologyType);
	};
}
