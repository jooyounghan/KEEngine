#pragma once
#include "DescriptorHeap.h"

namespace ke
{
	class RenderTargetResource
	{
	public:
		RenderTargetResource() = default;
		~RenderTargetResource();

	public:
		void init(
			ID3D12Device* device,
			DescriptorHeap& heap,
			uint32_t width,
			uint32_t height,
			DXGI_FORMAT format);
		void initFromSwapChain(
			ID3D12Device* device,
			DescriptorHeap& heap,
			ID3D12Resource* swapChainBuffer);
		void destroy();

	public:
		inline ID3D12Resource* getResource() const { return _resource.Get(); }
		inline const DescriptorHandle& getDescriptorHandle() const { return _descriptorHandle; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource>	_resource;
		DescriptorHandle						_descriptorHandle;
		DescriptorHeap*							_heap = nullptr;
		bool									_ownsResource = false;
	};
}
