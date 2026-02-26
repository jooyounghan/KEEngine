#include "GraphicsSystemPch.h"
#include "InputLayoutElement.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(InputLayoutElement)
		DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _semanticName)
		DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _semanticIndex)
		DEFINE_REFLECT_ENUM_PROPERTY(InputLayoutElement, _format)
		DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _inputSlot)
		DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _alignedByteOffset)
		DEFINE_REFLECT_ENUM_PROPERTY(InputLayoutElement, _inputSlotClass)
		DEFINE_REFLECT_POD_PROPERTY(InputLayoutElement, _instanceDataStepRate)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(InputLayoutElement)
		BIND_REFLECET_POD_PROPERTY(InputLayoutElement, FlyweightStringA, _semanticName, EReflectUIOption::Editable, FlyweightStringA::_empty);
		BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _semanticIndex, EReflectUIOption::Editable, 0, 15, 1, 0);
		BIND_REFLECET_POD_PROPERTY(InputLayoutElement, EDxgiFormat, _format, EReflectUIOption::Editable, EDxgiFormat::Unknown);
		BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _inputSlot, EReflectUIOption::Editable, 0, 15, 1, 0);
		BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _alignedByteOffset, EReflectUIOption::Editable, 0, 256, 1, 0);
		BIND_REFLECET_POD_PROPERTY(InputLayoutElement, EInputClassification, _inputSlotClass, EReflectUIOption::Editable, EInputClassification::PerVertexData);
		BIND_REFLECET_POD_RANGED_PROPERTY(InputLayoutElement, uint32, _instanceDataStepRate, EReflectUIOption::Editable, 0, 1000, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
