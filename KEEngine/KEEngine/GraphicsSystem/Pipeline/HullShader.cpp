#include "GraphicsSystemPch.h"
#include "HullShader.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(HullShader)
		DEFINE_REFLECT_PROPERTY(HullShader, std::string, _shaderPath)
		DEFINE_REFLECT_PROPERTY(HullShader, FlyweightStringA, _entryPoint)
		DEFINE_REFLECT_PROPERTY(HullShader, FlyweightStringA, _targetProfile)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(HullShader)
		BIND_REFLECT_PROPERTY(HullShader, std::string, _shaderPath, EReflectUIOption::Editable, std::string(""));
		BIND_REFLECT_PROPERTY(HullShader, FlyweightStringA, _entryPoint, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(HullShader, FlyweightStringA, _targetProfile, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()
}
