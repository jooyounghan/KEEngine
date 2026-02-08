#pragma once
#include "CommandQueue.h"

namespace ke
{
	class CommandManager;

	// ============================================================================
	// CommandContext - Base class for command recording
	// ============================================================================
	class CommandContext
	{
	public:
		CommandContext() = default;
		virtual ~CommandContext() = default;

		DELETE_COPYABLE(CommandContext);
		DEFAULT_MOVEABLE(CommandContext);

	public:
		void initialize(ID3D12Device* device, ECommandType type);
		void reset();
		CommandFence finish(CommandQueue& queue, bool waitForCompletion = false);

	public:
		inline ID3D12GraphicsCommandList4* getCommandList() const { return _commandList.Get(); }
		inline ECommandType getType() const { return _type; }

	public:
		// Resource barrier helpers
		void transitionBarrier(
			ID3D12Resource* resource,
			D3D12_RESOURCE_STATES before,
			D3D12_RESOURCE_STATES after,
			uint32 subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
		void uavBarrier(ID3D12Resource* resource = nullptr);
		void flushBarriers();

		// Descriptor heap binding
		void setDescriptorHeaps(uint32 count, ID3D12DescriptorHeap* const* heaps);

	protected:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>			_commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList4>		_commandList;
		ECommandType _type = ECommandType::Direct;

		static constexpr uint32 MAX_PENDING_BARRIERS = 16;
		D3D12_RESOURCE_BARRIER	_pendingBarriers[MAX_PENDING_BARRIERS] = {};
		uint32					_pendingBarrierCount = 0;
	};

	// ============================================================================
	// GraphicsCommandContext - Render commands, draw calls, DXR raytracing
	// ============================================================================
	class GraphicsCommandContext : public CommandContext
	{
	public:
		GraphicsCommandContext();

		// Render target management
		void setRenderTargets(
			uint32 numRTVs,
			const D3D12_CPU_DESCRIPTOR_HANDLE* rtvHandles,
			const D3D12_CPU_DESCRIPTOR_HANDLE* dsvHandle = nullptr);
		void clearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const float color[4]);
		void clearDepthStencil(
			D3D12_CPU_DESCRIPTOR_HANDLE dsv,
			float depth = 1.0f,
			uint8 stencil = 0);

		// Viewport / scissor
		void setViewport(
			float x, float y,
			float width, float height,
			float minDepth = 0.0f, float maxDepth = 1.0f);
		void setScissorRect(int32 left, int32 top, int32 right, int32 bottom);
		void setViewportAndScissor(uint32 x, uint32 y, uint32 width, uint32 height);

		// Pipeline state
		void setPipelineState(ID3D12PipelineState* pso);
		void setGraphicsRootSignature(ID3D12RootSignature* rootSig);
		void setGraphicsRootDescriptorTable(uint32 rootParamIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);
		void setGraphicsRoot32BitConstants(
			uint32 rootParamIndex, uint32 numValues,
			const void* data, uint32 destOffset = 0);
		void setGraphicsRootConstantBufferView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation);
		void setGraphicsRootShaderResourceView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation);

		// Draw commands
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);
		void setVertexBuffers(uint32 startSlot, uint32 count, const D3D12_VERTEX_BUFFER_VIEW* views);
		void setIndexBuffer(const D3D12_INDEX_BUFFER_VIEW* view);

		void draw(
			uint32 vertexCount, uint32 instanceCount = 1,
			uint32 startVertex = 0, uint32 startInstance = 0);
		void drawIndexed(
			uint32 indexCount, uint32 instanceCount = 1,
			uint32 startIndex = 0, int32 baseVertex = 0,
			uint32 startInstance = 0);
		void drawIndirect(
			ID3D12CommandSignature* commandSig,
			ID3D12Resource* argBuffer,
			uint64 argBufferOffset,
			uint32 maxCommandCount,
			ID3D12Resource* countBuffer = nullptr,
			uint64 countBufferOffset = 0);

		// Raytracing (DXR) commands
		void buildRaytracingAccelerationStructure(
			const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* desc,
			uint32 numPostbuildInfoDescs = 0,
			const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* postbuildInfoDescs = nullptr);
		void dispatchRays(const D3D12_DISPATCH_RAYS_DESC* desc);
	};

	// ============================================================================
	// ComputeCommandContext - Compute dispatch, indirect dispatch, GPU collision
	// ============================================================================
	class ComputeCommandContext : public CommandContext
	{
	public:
		ComputeCommandContext();

		// Pipeline state
		void setPipelineState(ID3D12PipelineState* pso);
		void setComputeRootSignature(ID3D12RootSignature* rootSig);
		void setComputeRootDescriptorTable(uint32 rootParamIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle);
		void setComputeRoot32BitConstants(
			uint32 rootParamIndex, uint32 numValues,
			const void* data, uint32 destOffset = 0);
		void setComputeRootConstantBufferView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation);
		void setComputeRootShaderResourceView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation);
		void setComputeRootUnorderedAccessView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation);

		// Dispatch commands
		void dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ);
		void dispatchIndirect(
			ID3D12CommandSignature* commandSig,
			ID3D12Resource* argBuffer,
			uint64 argBufferOffset,
			uint32 maxCommandCount,
			ID3D12Resource* countBuffer = nullptr,
			uint64 countBufferOffset = 0);
	};

	// ============================================================================
	// CopyCommandContext - Data upload, buffer/texture copy
	// ============================================================================
	class CopyCommandContext : public CommandContext
	{
	public:
		CopyCommandContext();

		// Buffer copy
		void copyBufferRegion(
			ID3D12Resource* dst, uint64 dstOffset,
			ID3D12Resource* src, uint64 srcOffset,
			uint64 numBytes);

		// Texture copy
		void copyTextureRegion(
			const D3D12_TEXTURE_COPY_LOCATION* dst,
			uint32 dstX, uint32 dstY, uint32 dstZ,
			const D3D12_TEXTURE_COPY_LOCATION* src,
			const D3D12_BOX* srcBox = nullptr);

		// Whole resource copy
		void copyResource(ID3D12Resource* dst, ID3D12Resource* src);
	};
}
