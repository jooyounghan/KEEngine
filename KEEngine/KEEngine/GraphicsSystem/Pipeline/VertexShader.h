#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(VertexShader)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(VertexShader);

	public:
		DECLARE_REFLECT_PROPERTY(std::string, _shaderPath);
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _entryPoint);
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _targetProfile);
	};
}
