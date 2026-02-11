#include "GraphicsSystemPch.h"
#include "GeometryShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(GeometryShader)
		DEFINE_REFLECT_PROPERTY(GeometryShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(GeometryShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(GeometryShader)
		BIND_REFLECT_PROPERTY(GeometryShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(GeometryShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
