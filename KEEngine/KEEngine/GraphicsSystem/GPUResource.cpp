#include "GraphicsSystemPch.h"
#include "GPUResource.h"

namespace ke
{
	void* GPUResource::map(uint32 subresource, const D3D12_RANGE* readRange)
	{
		KE_ASSERT(_resource, "Resource is not initialized.");

		void* mappedData = nullptr;
		D3D12_RANGE emptyRange = { 0, 0 };
		const D3D12_RANGE* range = readRange ? readRange : &emptyRange;

		KE_ASSERT(!FAILED(_resource->Map(subresource, range, &mappedData)),
			"Failed to map resource.");

		return mappedData;
	}

	void GPUResource::unmap(uint32 subresource, const D3D12_RANGE* writtenRange)
	{
		KE_ASSERT(_resource, "Resource is not initialized.");
		_resource->Unmap(subresource, writtenRange);
	}

	D3D12_GPU_VIRTUAL_ADDRESS GPUResource::getGPUVirtualAddress() const
	{
		KE_ASSERT(_resource, "Resource is not initialized.");
		return _resource->GetGPUVirtualAddress();
	}

	void GPUResource::releaseDescriptor()
	{
		if (_ownerHeap != nullptr && _descriptorHandle.isValid())
		{
			_ownerHeap->release(_descriptorHandle);
			_descriptorHandle = {};
			_ownerHeap = nullptr;
		}
	}
}
