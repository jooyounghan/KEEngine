#include "GraphicsSystemPch.h"
#include "SampleMask.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(SampleMask)
		DEFINE_REFLECT_POD_PROPERTY(SampleMask, _sampleMask)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(SampleMask)
		BIND_REFLECET_POD_RANGED_PROPERTY(SampleMask, uint32, _sampleMask, EReflectUIOption::Editable, 0xFFFFFFFF, 0, 0xFFFFFFFF, 1);
	END_BIND_REFLECT_PROPERTY()
}
