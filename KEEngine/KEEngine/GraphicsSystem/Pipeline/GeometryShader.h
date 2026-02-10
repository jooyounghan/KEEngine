#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(GeometryShader)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(GeometryShader);

	public:
		DECLARE_REFLECT_PROPERTY(std::string, _shaderPath);
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _entryPoint);
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _targetProfile);
	};
}
