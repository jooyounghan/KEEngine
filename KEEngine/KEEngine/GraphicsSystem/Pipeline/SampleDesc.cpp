#include "GraphicsSystemPch.h"
#include "SampleDesc.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(SampleDesc)
		DEFINE_REFLECT_PROPERTY(SampleDesc, uint32, _count)
		DEFINE_REFLECT_PROPERTY(SampleDesc, uint32, _quality)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(SampleDesc)
		BIND_REFLECT_PROPERTY(SampleDesc, uint32, _count, EReflectUIOption::Editable, 1, 32, 1, 1);
		BIND_REFLECT_PROPERTY(SampleDesc, uint32, _quality, EReflectUIOption::Editable, 0, 128, 1, 0);
	END_BIND_REFLECT_PROPERTY()
}
