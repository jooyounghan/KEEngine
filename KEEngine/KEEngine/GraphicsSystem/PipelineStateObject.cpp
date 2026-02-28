#include "GraphicsSystemPch.h"
#include "PipelineStateObject.h"
#include "DeviceManager.h"

namespace ke
{
	KE_DEFINE_REFLECT_ENUM_FLAG(EPipelineStateKey,
		FillWireframe, CullBack,
		UseDepthTest, UseDepthWrite,
		UseStencilTest, BlendAlpha
	);

	KE_BEGIN_DEFINE_REFLECT_PROPERTY(PipelineStateObject)
		KE_DEFINE_REFLECT_POD_PROPERTY(PipelineStateObject, _name);
		KE_DEFINE_REFLECT_ENUM_PROPERTY(PipelineStateObject, _stateKey);
		KE_DEFINE_REFLECT_POD_PROPERTY(PipelineStateObject, _stencilReadMask);
		KE_DEFINE_REFLECT_POD_PROPERTY(PipelineStateObject, _stencilWriteMask);
		KE_DEFINE_REFLECT_SEQ_PROPERTY(PipelineStateObject, _renderTargetFormats);
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(PipelineStateObject)
		KE_BIND_REFLECT_POD_PROPERTY(PipelineStateObject, FlyweightStringA, _name, EReflectUIOption::Editable, "")
		KE_BIND_REFLECT_ENUM_PROPERTY(PipelineStateObject, EPipelineStateKey, _stateKey, EReflectUIOption::Editable, EPipelineStateKey::UseDepthTest | EPipelineStateKey::UseDepthWrite | EPipelineStateKey::CullBack);
		KE_BIND_REFLECT_POD_PROPERTY(PipelineStateObject, uint8, _stencilReadMask, EReflectUIOption::Editable, D3D12_DEFAULT_STENCIL_READ_MASK);
		KE_BIND_REFLECT_POD_PROPERTY(PipelineStateObject, uint8, _stencilWriteMask, EReflectUIOption::Editable, D3D12_DEFAULT_STENCIL_WRITE_MASK);
		KE_BIND_REFLECET_PROPERTY(PipelineStateObject, std::vector<DXGI_FORMAT>, _renderTargetFormats, EReflectUIOption::Editable);
	KE_END_BIND_REFLECT_PROPERTY()


	void PipelineStateObject::initializePipelineStateObject()
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

		// Blend State
		{
			psoDesc.BlendState.AlphaToCoverageEnable = FALSE;
			psoDesc.BlendState.IndependentBlendEnable = FALSE;

			D3D12_RENDER_TARGET_BLEND_DESC rtDesc = {};
			rtDesc.BlendEnable = EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::BlendAlpha) ? TRUE : FALSE;
			rtDesc.LogicOpEnable = FALSE;
			rtDesc.SrcBlend = EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::BlendAlpha) ? D3D12_BLEND_SRC_ALPHA : D3D12_BLEND_ONE;
			rtDesc.DestBlend = EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::BlendAlpha) ? D3D12_BLEND_INV_SRC_ALPHA : D3D12_BLEND_ZERO;
			rtDesc.BlendOp = D3D12_BLEND_OP_ADD;
			rtDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
			rtDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
			rtDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
			rtDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
			rtDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			for (int i = 0; i < 8; ++i)
			{
				psoDesc.BlendState.RenderTarget[i] = rtDesc;
			}
		}

		// Rasterizer State
		psoDesc.RasterizerState =
		{
			EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::FillWireframe) ? D3D12_FILL_MODE_WIREFRAME : D3D12_FILL_MODE_SOLID,	// FillMode
			EnumUtil::isEnumFlagOn(_stateKey, EPipelineStateKey::CullBack) ? D3D12_CULL_MODE_BACK : D3D12_CULL_MODE_NONE,				// CullMode
			FALSE,																														// FrontCounterClockwise
			0,																															// DepthBias
			0.0f,																														// DepthBiasClamp
			0.0f,																														// SlopeScaledDepthBias
			FALSE,																														// DepthClipEnable
			FALSE,																														// MultisampleEnable
			FALSE,																														// AntialiasedLineEnable
			0,																															// ForcedSampleCount
			D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF																					// ConservativeRaster
		};

		// Depth Stencil State
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

		DeviceManager::getInstance().getDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_pipelineStateObject));
	}
}
