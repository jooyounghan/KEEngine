#include "GraphicsSystemPch.h"
#include "VertexShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(VertexShader)
		DEFINE_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _shaderPath)
		DEFINE_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(VertexShader)
		BIND_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _shaderPath, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(VertexShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
