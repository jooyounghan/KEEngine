#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(InputLayoutElement)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(InputLayoutElement);

	public:
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _semanticName);
		DECLARE_REFLECT_PROPERTY(uint32, _semanticIndex);
		DECLARE_REFLECT_PROPERTY(uint8, _format);
		DECLARE_REFLECT_PROPERTY(uint32, _inputSlot);
		DECLARE_REFLECT_PROPERTY(uint32, _alignedByteOffset);
		DECLARE_REFLECT_PROPERTY(uint8, _inputSlotClass);
		DECLARE_REFLECT_PROPERTY(uint32, _instanceDataStepRate);
	};
}
