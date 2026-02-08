#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"

namespace ke
{
	// ============================================================================
	// RenderTargetBuffer - GPU resource with an associated RTV descriptor
	//
	// Can be created as a standalone render target or initialized from an
	// existing swap chain back buffer.
	// ============================================================================
	class RenderTargetBuffer : public GPUResource
	{
	public:
		RenderTargetBuffer() = default;
		~RenderTargetBuffer() override;

		DELETE_COPYABLE(RenderTargetBuffer);
		DEFAULT_MOVEABLE(RenderTargetBuffer);

	public:
		void initialize(
			ID3D12Device* device,
			uint32 width, uint32 height,
			DXGI_FORMAT format,
			DescriptorHeap* rtvHeap,
			const float* clearColor = nullptr);

		void initializeFromSwapChain(
			ID3D12Device* device,
			ID3D12Resource* backBuffer,
			DescriptorHeap* rtvHeap);

		void shutdown();

	public:
		inline D3D12_CPU_DESCRIPTOR_HANDLE getRTV() const { return _rtvHandle.cpuHandle; }
		inline const DescriptorHandle& getDescriptorHandle() const { return _rtvHandle; }
		inline uint32 getWidth() const { return _width; }
		inline uint32 getHeight() const { return _height; }
		inline DXGI_FORMAT getFormat() const { return _format; }

	private:
		DescriptorHeap*		_ownerHeap = nullptr;
		DescriptorHandle	_rtvHandle;
		uint32				_width = 0;
		uint32				_height = 0;
		DXGI_FORMAT			_format = DXGI_FORMAT_UNKNOWN;
	};
}
