#include "GraphicsSystemPch.h"
#include "PixelShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(PixelShader)
		DEFINE_REFLECT_PROPERTY(PixelShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(PixelShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(PixelShader)
		BIND_REFLECT_PROPERTY(PixelShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(PixelShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
