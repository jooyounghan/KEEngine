#pragma once
#include "DescriptorHeap.h"

namespace ke
{
	// ============================================================================
	// GPUResource - Base wrapper for ID3D12Resource with map/unmap support
	//
	// All derived classes that need a descriptor (CBV, SRV, RTV, etc.) share
	// the _ownerHeap / _descriptorHandle pair managed here.
	// ============================================================================
	class GPUResource
	{
	public:
		GPUResource() = default;
		virtual ~GPUResource() = default;
		NONCOPYABLE(GPUResource);

	public:
		void* map(uint32 subresource = 0, const D3D12_RANGE* readRange = nullptr);
		void unmap(uint32 subresource = 0, const D3D12_RANGE* writtenRange = nullptr);

	public:
		inline ID3D12Resource* getResource() const { return _resource.Get(); }
		D3D12_GPU_VIRTUAL_ADDRESS getGPUVirtualAddress() const;

	public:
		inline const DescriptorHandle& getDescriptorHandle() const { return _descriptorHandle; }
		inline uint32 getBindlessIndex() const { return _descriptorHandle.heapIndex; }

	protected:
		void releaseDescriptor();

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource> _resource;
		DescriptorHeap*		_ownerHeap = nullptr;
		DescriptorHandle	_descriptorHandle;
	};
}
