#pragma once

namespace ke
{
	class VertexShader;
	class PixelShader;
	class GeometryShader;
	class DomainShader;
	class HullShader;
	class ComputeShader;
	class InputLayoutElement;
	class BlendState;
	class RasterizerState;
	class DepthState;
	class StencilState;
	class RenderTargetFormats;
	class DepthStencilFormat;
	class SampleDesc;
	class SampleMask;
	class PrimitiveTopology;

	struct GraphicsPipelineDesc
	{
		VertexShader* vertexShader = nullptr;
		PixelShader* pixelShader = nullptr;
		GeometryShader* geometryShader = nullptr;
		DomainShader* domainShader = nullptr;
		HullShader* hullShader = nullptr;

		const std::vector<InputLayoutElement*>* inputLayout = nullptr;
		PrimitiveTopology* primitiveTopology = nullptr;
		BlendState* blendState = nullptr;
		RasterizerState* rasterizerState = nullptr;
		DepthState* depthState = nullptr;
		StencilState* stencilState = nullptr;
		RenderTargetFormats* renderTargetFormats = nullptr;
		DepthStencilFormat* depthStencilFormat = nullptr;
		SampleDesc* sampleDesc = nullptr;
		SampleMask* sampleMask = nullptr;

		ID3D12RootSignature* rootSignature = nullptr;
	};

	struct ComputePipelineDesc
	{
		ComputeShader* computeShader = nullptr;
		ID3D12RootSignature* rootSignature = nullptr;
	};

	class PipelineStateManager
	{
	public:
		PipelineStateManager();
		~PipelineStateManager();

	private:
		ID3D12Device* _device = nullptr;
		std::unordered_map<size_t, Microsoft::WRL::ComPtr<ID3D12PipelineState>> _pipelineStates;

	public:
		void initialize(ID3D12Device* device);

	public:
		ID3D12PipelineState* getOrCreateGraphicsPipelineState(const GraphicsPipelineDesc& desc);
		ID3D12PipelineState* getOrCreateComputePipelineState(const ComputePipelineDesc& desc);

	private:
		size_t computeGraphicsPipelineHash(const GraphicsPipelineDesc& desc);
		size_t computeComputePipelineHash(const ComputePipelineDesc& desc);
		
		ID3D12PipelineState* createGraphicsPipelineState(const GraphicsPipelineDesc& desc);
		ID3D12PipelineState* createComputePipelineState(const ComputePipelineDesc& desc);
	};
}
