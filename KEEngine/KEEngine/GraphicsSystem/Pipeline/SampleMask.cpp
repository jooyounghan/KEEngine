#include "GraphicsSystemPch.h"
#include "SampleMask.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(SampleMask)
		DEFINE_REFLECT_PROPERTY(SampleMask, uint32, _sampleMask)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(SampleMask)
		BIND_REFLECT_PROPERTY(SampleMask, uint32, _sampleMask, EReflectUIOption::Editable, 0, 4294967295, 1, 0xFFFFFFFF);
	END_BIND_REFLECT_PROPERTY()
}
