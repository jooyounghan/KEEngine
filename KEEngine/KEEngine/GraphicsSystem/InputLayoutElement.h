#pragma once
#include "ReflectObject.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_REFLECT_OBJECT_CLASS(InputLayoutElement)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(InputLayoutElement);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(FlyweightStringA, _semanticName, FlyweightStringA::_empty);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _semanticIndex, 0);
		KE_DECLARE_REFLECT_PROPERTY(EDXGIFormat, _format);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _inputSlot, 0);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _alignedByteOffset, 0);
		KE_DECLARE_REFLECT_PROPERTY(EInputClassification, _inputSlotClass);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _instanceDataStepRate, 0);
	};
}
