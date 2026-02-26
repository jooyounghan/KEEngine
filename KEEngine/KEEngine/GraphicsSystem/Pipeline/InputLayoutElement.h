#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(InputLayoutElement)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(InputLayoutElement);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(FlyweightStringA, _semanticName, FlyweightStringA::_empty);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _semanticIndex, 0);
		DECLARE_REFLECT_PROPERTY(EDxgiFormat, _format);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _inputSlot, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _alignedByteOffset, 0);
		DECLARE_REFLECT_PROPERTY(EInputClassification, _inputSlotClass);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _instanceDataStepRate, 0);
	};
}
