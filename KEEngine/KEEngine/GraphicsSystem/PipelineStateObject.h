#pragma once
#include "ReflectObject.h"
#include "EnumUtil.h"

namespace ke
{
	KE_DECLARE_REFLECT_ENUM_FLAG(EPipelineStateKey, uint32)
	enum class EPipelineStateKey : uint32
	{
		UseDepthTest = 1 << 0,
		UseDepthWrite = 1 << 1,
		UseStencilTest = 1 << 2,
		BlendAlpha = 1 << 3,
		CullBack = 1 << 4,
	};

	KE_REFLECT_OBJECT_CLASS(PipelineStateObject)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(PipelineStateObject);

	protected:
		KE_DECLARE_REFLECT_PROPERTY(FlyweightStringA, _name);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EPipelineStateKey, _stateKey, EPipelineStateKey::UseDepthTest | EPipelineStateKey::UseDepthWrite | EPipelineStateKey::CullBack);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilReadMask, D3D12_DEFAULT_STENCIL_READ_MASK);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint8, _stencilWriteMask, D3D12_DEFAULT_STENCIL_WRITE_MASK);

	protected:
		void initializePipelineStateObject();
	};
}

