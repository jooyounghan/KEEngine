#include "GraphicsSystemPch.h"
#include "InputLayoutElement.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(InputLayoutElement)
		KE_DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _semanticName)
		KE_DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _semanticIndex)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(InputLayoutElement, _format)
		KE_DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _inputSlot)
		KE_DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _alignedByteOffset)
		KE_DEFINE_REFLECT_ENUM_PROPERTY(InputLayoutElement, _inputSlotClass)
		KE_DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _instanceDataStepRate)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(InputLayoutElement)
		KE_BIND_REFLECT_POD_PROPERTY(InputLayoutElement, FlyweightStringA, _semanticName, EReflectUIOption::Editable, FlyweightStringA::_empty);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _semanticIndex, EReflectUIOption::Editable, 0, 15, 1, 0);
		KE_BIND_REFLECT_POD_PROPERTY(InputLayoutElement, EDxgiFormat, _format, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _inputSlot, EReflectUIOption::Editable, 0, 15, 1, 0);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _alignedByteOffset, EReflectUIOption::Editable, 0, 256, 1, 0);
		KE_BIND_REFLECT_POD_PROPERTY(InputLayoutElement, EInputClassification, _inputSlotClass, EReflectUIOption::Editable, EInputClassification::PerVertexData);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _instanceDataStepRate, EReflectUIOption::Editable, 0, 1000, 1, 0);
	KE_END_BIND_REFLECT_PROPERTY()
}
