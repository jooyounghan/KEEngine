#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(HullShader)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(HullShader);

	public:
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _entryPoint);
		DECLARE_REFLECT_PROPERTY(FlyweightStringA, _targetProfile);

	public:
		std::vector<uint8> _compiledBytecode;

	public:
		inline D3D12_SHADER_BYTECODE getShaderBytecode() const
		{
			D3D12_SHADER_BYTECODE bytecode = {};
			bytecode.pShaderBytecode = _compiledBytecode.data();
			bytecode.BytecodeLength = _compiledBytecode.size();
			return bytecode;
		}
	};
}
