#include "GraphicsSystemPch.h"
#include "PipelineStateObject.h"

namespace ke
{
	KE_BEGIN_DEFINE_REFLECT_PROPERTY(PipelineStateObject)
		KE_DEFINE_REFLECT_POD_PROPERTY(PipelineStateObject, _name);
		KE_DEFINE_REFLECT_ENUM_PROPERTY(PipelineStateObject, _stateKey);
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(PipelineStateObject)
		KE_BIND_REFLECT_POD_PROPERTY(PipelineStateObject, FlyweightStringA, _name, EReflectUIOption::Editable, "")
		KE_BIND_REFLECT_ENUM_PROPERTY(PipelineStateObject, EPipelineStateKey, _stateKey, EReflectUIOption::Editable, EPipelineStateKey::UseDepthTest | EPipelineStateKey::UseDepthWrite | EPipelineStateKey::CullBack);
	KE_END_BIND_REFLECT_PROPERTY()


	void PipelineStateObject::initializePipelineStateObject()
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.DepthStencilState =
		{
			EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::UseDepthTest) ? TRUE : FALSE,												// DepthEnable
			EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::UseDepthWrite) ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO,	// DepthWriteMask
			D3D12_COMPARISON_FUNC::D3D12_COMPARISON_FUNC_LESS,																				// DepthFunc
			EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::UseStencilTest) ? TRUE : FALSE,											// StencilEnable
			_stencilReadMask,																												// StencilReadMask
			_stencilWriteMask,																												// StencilWriteMask
			{																																// FrontFace
				D3D12_STENCIL_OP_KEEP,																										// StencilFailOp
				D3D12_STENCIL_OP_KEEP,																										// StencilDepthFailOp
				D3D12_STENCIL_OP_KEEP,																										// StencilPassOp
				D3D12_COMPARISON_FUNC::D3D12_COMPARISON_FUNC_ALWAYS,																		// StencilFunc
			},
			{																																// BackFace
				D3D12_STENCIL_OP_KEEP,																										// StencilFailOp
				D3D12_STENCIL_OP_KEEP,																										// StencilDepthFailOp
				D3D12_STENCIL_OP_KEEP,																										// StencilPassOp
				D3D12_COMPARISON_FUNC::D3D12_COMPARISON_FUNC_ALWAYS,																		// StencilFunc
			}
		};

		if (EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::UseDepthTest))
		{

		}
	}
}
