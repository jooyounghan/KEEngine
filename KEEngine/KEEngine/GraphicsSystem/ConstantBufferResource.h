#pragma once
#include "DescriptorHeap.h"

namespace ke
{
	class ConstantBufferResource
	{
	public:
		ConstantBufferResource() = default;
		~ConstantBufferResource();

	public:
		void init(ID3D12Device* device, DescriptorHeap& heap, uint32_t bufferSize);
		void destroy();

	public:
		void* map();
		void unmap();
		void upload(const void* data, uint32_t size);

	public:
		inline ID3D12Resource* getResource() const { return _resource.Get(); }
		inline D3D12_GPU_VIRTUAL_ADDRESS getGPUVirtualAddress() const { return _resource ? _resource->GetGPUVirtualAddress() : 0; }
		inline const DescriptorHandle& getDescriptorHandle() const { return _descriptorHandle; }
		inline uint32_t getBufferSize() const { return _bufferSize; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource>	_resource;
		DescriptorHandle						_descriptorHandle;
		DescriptorHeap*							_heap = nullptr;
		uint32_t								_bufferSize = 0;
		void*									_mappedData = nullptr;
	};
}
