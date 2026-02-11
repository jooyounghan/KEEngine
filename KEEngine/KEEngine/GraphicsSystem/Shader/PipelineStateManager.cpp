#include "GraphicsSystemPch.h"
#include "PipelineStateManager.h"
#include "Pipeline/VertexShader.h"
#include "Pipeline/PixelShader.h"
#include "Pipeline/GeometryShader.h"
#include "Pipeline/DomainShader.h"
#include "Pipeline/HullShader.h"
#include "Pipeline/ComputeShader.h"
#include "Pipeline/InputLayoutElement.h"
#include "Pipeline/BlendState.h"
#include "Pipeline/RasterizerState.h"
#include "Pipeline/DepthState.h"
#include "Pipeline/StencilState.h"
#include "Pipeline/RenderTargetFormats.h"
#include "Pipeline/DepthStencilFormat.h"
#include "Pipeline/SampleDesc.h"
#include "Pipeline/SampleMask.h"
#include "Pipeline/PrimitiveTopology.h"

namespace ke
{
	PipelineStateManager::PipelineStateManager()
	{
	}

	PipelineStateManager::~PipelineStateManager()
	{
	}

	void PipelineStateManager::initialize(ID3D12Device* device)
	{
		_device = device;
	}

	ID3D12PipelineState* PipelineStateManager::getOrCreateGraphicsPipelineState(const GraphicsPipelineDesc& desc)
	{
		size_t hash = computeGraphicsPipelineHash(desc);
		
		auto it = _pipelineStates.find(hash);
		if (it != _pipelineStates.end())
		{
			return it->second.Get();
		}

		auto pso = createGraphicsPipelineState(desc);
		if (pso)
		{
			_pipelineStates[hash] = pso;
			return pso.Get();
		}
		return nullptr;
	}

	ID3D12PipelineState* PipelineStateManager::getOrCreateComputePipelineState(const ComputePipelineDesc& desc)
	{
		size_t hash = computeComputePipelineHash(desc);
		
		auto it = _pipelineStates.find(hash);
		if (it != _pipelineStates.end())
		{
			return it->second.Get();
		}

		auto pso = createComputePipelineState(desc);
		if (pso)
		{
			_pipelineStates[hash] = pso;
			return pso.Get();
		}
		return nullptr;
	}

	size_t PipelineStateManager::computeGraphicsPipelineHash(const GraphicsPipelineDesc& desc)
	{
		size_t hash = 0;
		
		// Improved hash combining using multiplication and XOR
		auto combineHash = [&hash](size_t newHash) {
			hash ^= newHash + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		};
		
		// Hash shader pointers
		combineHash(std::hash<void*>{}(desc.vertexShader));
		combineHash(std::hash<void*>{}(desc.pixelShader));
		combineHash(std::hash<void*>{}(desc.geometryShader));
		combineHash(std::hash<void*>{}(desc.domainShader));
		combineHash(std::hash<void*>{}(desc.hullShader));
		
		// Hash pipeline state components
		combineHash(std::hash<void*>{}(desc.inputLayout));
		combineHash(std::hash<void*>{}(desc.primitiveTopology));
		combineHash(std::hash<void*>{}(desc.blendState));
		combineHash(std::hash<void*>{}(desc.rasterizerState));
		combineHash(std::hash<void*>{}(desc.depthState));
		combineHash(std::hash<void*>{}(desc.stencilState));
		combineHash(std::hash<void*>{}(desc.renderTargetFormats));
		combineHash(std::hash<void*>{}(desc.depthStencilFormat));
		combineHash(std::hash<void*>{}(desc.sampleDesc));
		combineHash(std::hash<void*>{}(desc.sampleMask));
		combineHash(std::hash<void*>{}(desc.rootSignature));
		
		return hash;
	}

	size_t PipelineStateManager::computeComputePipelineHash(const ComputePipelineDesc& desc)
	{
		size_t hash = 0;
		
		// Improved hash combining using multiplication and XOR
		auto combineHash = [&hash](size_t newHash) {
			hash ^= newHash + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		};
		
		combineHash(std::hash<void*>{}(desc.computeShader));
		combineHash(std::hash<void*>{}(desc.rootSignature));
		
		return hash;
	}

	Microsoft::WRL::ComPtr<ID3D12PipelineState> PipelineStateManager::createGraphicsPipelineState(const GraphicsPipelineDesc& desc)
	{
		if (!_device || !desc.vertexShader || !desc.rootSignature)
			return nullptr;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.pRootSignature = desc.rootSignature;

		// Set shaders
		psoDesc.VS = desc.vertexShader->getShaderBytecode();
		if (desc.pixelShader)
			psoDesc.PS = desc.pixelShader->getShaderBytecode();
		if (desc.geometryShader)
			psoDesc.GS = desc.geometryShader->getShaderBytecode();
		if (desc.domainShader)
			psoDesc.DS = desc.domainShader->getShaderBytecode();
		if (desc.hullShader)
			psoDesc.HS = desc.hullShader->getShaderBytecode();

		// Set input layout
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputElements;
		if (desc.inputLayout && !desc.inputLayout->empty())
		{
			for (const auto* element : *desc.inputLayout)
			{
				D3D12_INPUT_ELEMENT_DESC d3dElement = {};
				d3dElement.SemanticName = element->_semanticName.c_str();
				d3dElement.SemanticIndex = element->_semanticIndex;
				d3dElement.Format = static_cast<DXGI_FORMAT>(element->_format);
				d3dElement.InputSlot = element->_inputSlot;
				d3dElement.AlignedByteOffset = element->_alignedByteOffset;
				d3dElement.InputSlotClass = static_cast<D3D12_INPUT_CLASSIFICATION>(element->_inputSlotClass);
				d3dElement.InstanceDataStepRate = element->_instanceDataStepRate;
				inputElements.push_back(d3dElement);
			}
			psoDesc.InputLayout.pInputElementDescs = inputElements.data();
			psoDesc.InputLayout.NumElements = static_cast<UINT>(inputElements.size());
		}

		// Set primitive topology type
		if (desc.primitiveTopology)
		{
			psoDesc.PrimitiveTopologyType = static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(desc.primitiveTopology->_primitiveTopologyType);
		}
		else
		{
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		}

		// Set blend state
		if (desc.blendState)
		{
			psoDesc.BlendState.AlphaToCoverageEnable = desc.blendState->_alphaToCoverageEnable;
			psoDesc.BlendState.IndependentBlendEnable = desc.blendState->_independentBlendEnable;
			psoDesc.BlendState.RenderTarget[0].BlendEnable = desc.blendState->_blendEnable;
			psoDesc.BlendState.RenderTarget[0].SrcBlend = static_cast<D3D12_BLEND>(desc.blendState->_srcBlend);
			psoDesc.BlendState.RenderTarget[0].DestBlend = static_cast<D3D12_BLEND>(desc.blendState->_destBlend);
			psoDesc.BlendState.RenderTarget[0].BlendOp = static_cast<D3D12_BLEND_OP>(desc.blendState->_blendOp);
			psoDesc.BlendState.RenderTarget[0].SrcBlendAlpha = static_cast<D3D12_BLEND>(desc.blendState->_srcBlendAlpha);
			psoDesc.BlendState.RenderTarget[0].DestBlendAlpha = static_cast<D3D12_BLEND>(desc.blendState->_destBlendAlpha);
			psoDesc.BlendState.RenderTarget[0].BlendOpAlpha = static_cast<D3D12_BLEND_OP>(desc.blendState->_blendOpAlpha);
			psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = desc.blendState->_renderTargetWriteMask;
		}
		else
		{
			// Default blend state
			psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		}

		// Set rasterizer state
		if (desc.rasterizerState)
		{
			psoDesc.RasterizerState.FillMode = static_cast<D3D12_FILL_MODE>(desc.rasterizerState->_fillMode);
			psoDesc.RasterizerState.CullMode = static_cast<D3D12_CULL_MODE>(desc.rasterizerState->_cullMode);
			psoDesc.RasterizerState.FrontCounterClockwise = desc.rasterizerState->_frontCounterClockwise;
			psoDesc.RasterizerState.DepthBias = desc.rasterizerState->_depthBias;
			psoDesc.RasterizerState.DepthBiasClamp = desc.rasterizerState->_depthBiasClamp;
			psoDesc.RasterizerState.SlopeScaledDepthBias = desc.rasterizerState->_slopeScaledDepthBias;
			psoDesc.RasterizerState.DepthClipEnable = desc.rasterizerState->_depthClipEnable;
			psoDesc.RasterizerState.MultisampleEnable = desc.rasterizerState->_multisampleEnable;
			psoDesc.RasterizerState.AntialiasedLineEnable = desc.rasterizerState->_antialiasedLineEnable;
			psoDesc.RasterizerState.ForcedSampleCount = desc.rasterizerState->_forcedSampleCount;
			psoDesc.RasterizerState.ConservativeRaster = static_cast<D3D12_CONSERVATIVE_RASTERIZATION_MODE>(desc.rasterizerState->_conservativeRaster);
		}
		else
		{
			// Default rasterizer state
			psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
			psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
			psoDesc.RasterizerState.DepthClipEnable = TRUE;
		}

		// Set depth stencil state
		if (desc.depthState)
		{
			psoDesc.DepthStencilState.DepthEnable = desc.depthState->_depthEnable;
			psoDesc.DepthStencilState.DepthWriteMask = static_cast<D3D12_DEPTH_WRITE_MASK>(desc.depthState->_depthWriteMask);
			psoDesc.DepthStencilState.DepthFunc = static_cast<D3D12_COMPARISON_FUNC>(desc.depthState->_depthFunc);
		}
		else
		{
			// Default depth state
			psoDesc.DepthStencilState.DepthEnable = TRUE;
			psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		}

		// Set stencil state if available
		if (desc.stencilState)
		{
			psoDesc.DepthStencilState.StencilEnable = desc.stencilState->_stencilEnable;
			psoDesc.DepthStencilState.StencilReadMask = desc.stencilState->_stencilReadMask;
			psoDesc.DepthStencilState.StencilWriteMask = desc.stencilState->_stencilWriteMask;
			
			psoDesc.DepthStencilState.FrontFace.StencilFailOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_frontFaceStencilFailOp);
			psoDesc.DepthStencilState.FrontFace.StencilDepthFailOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_frontFaceStencilDepthFailOp);
			psoDesc.DepthStencilState.FrontFace.StencilPassOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_frontFaceStencilPassOp);
			psoDesc.DepthStencilState.FrontFace.StencilFunc = static_cast<D3D12_COMPARISON_FUNC>(desc.stencilState->_frontFaceStencilFunc);
			
			psoDesc.DepthStencilState.BackFace.StencilFailOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_backFaceStencilFailOp);
			psoDesc.DepthStencilState.BackFace.StencilDepthFailOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_backFaceStencilDepthFailOp);
			psoDesc.DepthStencilState.BackFace.StencilPassOp = static_cast<D3D12_STENCIL_OP>(desc.stencilState->_backFaceStencilPassOp);
			psoDesc.DepthStencilState.BackFace.StencilFunc = static_cast<D3D12_COMPARISON_FUNC>(desc.stencilState->_backFaceStencilFunc);
		}

		// Set render target formats
		if (desc.renderTargetFormats)
		{
			psoDesc.NumRenderTargets = desc.renderTargetFormats->_numRenderTargets;
			psoDesc.RTVFormats[0] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat0);
			psoDesc.RTVFormats[1] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat1);
			psoDesc.RTVFormats[2] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat2);
			psoDesc.RTVFormats[3] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat3);
			psoDesc.RTVFormats[4] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat4);
			psoDesc.RTVFormats[5] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat5);
			psoDesc.RTVFormats[6] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat6);
			psoDesc.RTVFormats[7] = static_cast<DXGI_FORMAT>(desc.renderTargetFormats->_rtvFormat7);
		}
		else
		{
			psoDesc.NumRenderTargets = 1;
			psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		}

		// Set depth stencil format
		if (desc.depthStencilFormat)
		{
			psoDesc.DSVFormat = static_cast<DXGI_FORMAT>(desc.depthStencilFormat->_dsvFormat);
		}
		else
		{
			psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		}

		// Set sample description
		if (desc.sampleDesc)
		{
			psoDesc.SampleDesc.Count = desc.sampleDesc->_count;
			psoDesc.SampleDesc.Quality = desc.sampleDesc->_quality;
		}
		else
		{
			psoDesc.SampleDesc.Count = 1;
			psoDesc.SampleDesc.Quality = 0;
		}

		// Set sample mask
		if (desc.sampleMask)
		{
			psoDesc.SampleMask = desc.sampleMask->_sampleMask;
		}
		else
		{
			psoDesc.SampleMask = UINT_MAX;
		}

		Microsoft::WRL::ComPtr<ID3D12PipelineState> pso;
		HRESULT hr = _device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso));
		if (FAILED(hr))
		{
			return nullptr;
		}

		return pso;
	}

	Microsoft::WRL::ComPtr<ID3D12PipelineState> PipelineStateManager::createComputePipelineState(const ComputePipelineDesc& desc)
	{
		if (!_device || !desc.computeShader || !desc.rootSignature)
			return nullptr;

		D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.pRootSignature = desc.rootSignature;
		psoDesc.CS = desc.computeShader->getShaderBytecode();

		Microsoft::WRL::ComPtr<ID3D12PipelineState> pso;
		HRESULT hr = _device->CreateComputePipelineState(&psoDesc, IID_PPV_ARGS(&pso));
		if (FAILED(hr))
		{
			return nullptr;
		}

		return pso;
	}
}
