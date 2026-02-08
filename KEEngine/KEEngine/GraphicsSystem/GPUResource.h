#pragma once

namespace ke
{
	struct DescriptorHandle;

	// ============================================================================
	// GPUResource - Base wrapper for ID3D12Resource with map/unmap support
	// ============================================================================
	class GPUResource
	{
	public:
		GPUResource() = default;
		virtual ~GPUResource() = default;

		DELETE_COPYABLE(GPUResource);
		DEFAULT_MOVEABLE(GPUResource);

	public:
		void* map(uint32 subresource = 0, const D3D12_RANGE* readRange = nullptr);
		void unmap(uint32 subresource = 0, const D3D12_RANGE* writtenRange = nullptr);

	public:
		inline ID3D12Resource* getResource() const { return _resource.Get(); }
		D3D12_GPU_VIRTUAL_ADDRESS getGPUVirtualAddress() const;

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource> _resource;
	};
}
