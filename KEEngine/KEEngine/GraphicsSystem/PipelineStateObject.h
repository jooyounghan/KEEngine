#pragma once
#include "ReflectObject.h"
#include "EnumUtil.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_DECLARE_REFLECT_ENUM_FLAG(EPipelineStateKey, uint32)
	enum class EPipelineStateKey : uint32
	{
		FillWireframe = 1 << 0,
		CullBack = 1 << 1,
		UseDepthTest = 1 << 2,
		UseDepthWrite = 1 << 3,
		UseStencilTest = 1 << 4,
		BlendAlpha = 1 << 5,

		USE_POINT_TOPOLOGY = 1 << 6,
		USE_LINE_TOPOLOGY = 1 << 7,
		USE_TRIANGLE_TOPOLOGY = 1 << 8,

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
		KE_DECLARE_REFLECT_PROPERTY(std::vector<EDXGIFormat>, _renderTargetFormats);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(EDXGIFormat, _depthStencilFormat, EDXGIFormat::D24_Unorm_S8_Uint);

	protected:
		Microsoft::WRL::ComPtr<ID3D12PipelineState> _pipelineStateObject;

	public:
		ID3D12PipelineState* getPipelineStateObject() const { return _pipelineStateObject.Get(); }

	protected:
		void initializePipelineStateObject();
	};
}

