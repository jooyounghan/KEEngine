#include "GraphicsSystemPch.h"
#include "SampleDesc.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(SampleDesc)
		KE_DEFINE_REFLECT_POD_PROPERTY(SampleDesc, _count)
		KE_DEFINE_REFLECT_POD_PROPERTY(SampleDesc, _quality)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(SampleDesc)
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(SampleDesc, uint32, _count, EReflectUIOption::Editable, 1, 32, 1, 1);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(SampleDesc, uint32, _quality, EReflectUIOption::Editable, 0, 128, 1, 0);
	KE_END_BIND_REFLECT_PROPERTY()
}
