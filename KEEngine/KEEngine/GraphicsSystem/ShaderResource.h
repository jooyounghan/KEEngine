#pragma once
#include "DescriptorHeap.h"

namespace ke
{
	class ShaderResource
	{
	public:
		ShaderResource() = default;
		~ShaderResource();

	public:
		void init(
			ID3D12Device* device,
			DescriptorHeap& heap,
			ID3D12Resource* resource,
			const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc);
		void destroy();

	public:
		inline const DescriptorHandle& getDescriptorHandle() const { return _descriptorHandle; }

	private:
		DescriptorHandle	_descriptorHandle;
		DescriptorHeap*		_heap = nullptr;
	};
}
