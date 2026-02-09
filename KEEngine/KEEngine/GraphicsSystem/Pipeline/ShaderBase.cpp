#include "GraphicsSystemPch.h"
#include "ShaderBase.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(ShaderBase)
		DEFINE_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _shaderPath)
		DEFINE_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(ShaderBase)
		BIND_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _shaderPath, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(ShaderBase, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
