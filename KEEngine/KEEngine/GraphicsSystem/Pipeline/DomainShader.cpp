#include "GraphicsSystemPch.h"
#include "DomainShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(DomainShader)
		DEFINE_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _shaderPath)
		DEFINE_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(DomainShader)
		BIND_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _shaderPath, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(DomainShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
