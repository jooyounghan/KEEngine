#include "GraphicsSystemPch.h"
#include "ComputeShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(ComputeShader)
		DEFINE_REFLECT_PROPERTY(ComputeShader, std::string, _shaderPath)
		DEFINE_REFLECT_PROPERTY(ComputeShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(ComputeShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(ComputeShader)
		BIND_REFLECT_PROPERTY(ComputeShader, std::string, _shaderPath, EReflectUIOption::Editable, std::string(""));
		BIND_REFLECT_PROPERTY(ComputeShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(ComputeShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
