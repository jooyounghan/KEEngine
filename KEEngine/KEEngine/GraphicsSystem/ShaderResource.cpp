#include "GraphicsSystemPch.h"
#include "ShaderResource.h"

namespace ke
{
	ShaderResource::~ShaderResource()
	{
		destroy();
	}

	void ShaderResource::init(
		ID3D12Device* device,
		DescriptorHeap& heap,
		ID3D12Resource* resource,
		const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");

		_heap = &heap;
		_descriptorHandle = heap.allocate();

		device->CreateShaderResourceView(resource, &srvDesc, _descriptorHandle.cpuHandle);
	}

	void ShaderResource::destroy()
	{
		if (_heap != nullptr && _descriptorHandle.isValid())
		{
			_heap->release(_descriptorHandle);
			_descriptorHandle = {};
		}

		_heap = nullptr;
	}
}
