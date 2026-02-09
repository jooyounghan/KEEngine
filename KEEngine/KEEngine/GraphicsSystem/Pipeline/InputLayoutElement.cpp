#include "GraphicsSystemPch.h"
#include "InputLayoutElement.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(InputLayoutElement)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, FlyweightStringA, _semanticName)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint32, _semanticIndex)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint8, _format)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint32, _inputSlot)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint32, _alignedByteOffset)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint8, _inputSlotClass)
		DEFINE_REFLECT_PROPERTY(InputLayoutElement, uint32, _instanceDataStepRate)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(InputLayoutElement)
		BIND_REFLECT_PROPERTY(InputLayoutElement, FlyweightStringA, _semanticName, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint32, _semanticIndex, EReflectUIOption::Editable, 0, 15, 1, 0);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint8, _format, EReflectUIOption::Editable, 0, 255, 1, 0);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint32, _inputSlot, EReflectUIOption::Editable, 0, 15, 1, 0);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint32, _alignedByteOffset, EReflectUIOption::Editable, 0, 256, 1, 0);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint8, _inputSlotClass, EReflectUIOption::Editable, 0, 1, 1, 0);
		BIND_REFLECT_PROPERTY(InputLayoutElement, uint32, _instanceDataStepRate, EReflectUIOption::Editable, 0, 1000, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
