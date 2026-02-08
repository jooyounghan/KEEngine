#include "GraphicsSystemPch.h"
#include "StructuredBufferResource.h"

namespace ke
{
	StructuredBufferResource::~StructuredBufferResource()
	{
		destroy();
	}

	void StructuredBufferResource::init(ID3D12Device* device, DescriptorHeap& heap, uint32_t elementSize, uint32_t elementCount)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(elementSize > 0, "Element size must be greater than 0.");
		KE_ASSERT(elementCount > 0, "Element count must be greater than 0.");

		_heap = &heap;
		_elementSize = elementSize;
		_elementCount = elementCount;

		const uint32_t totalSize = elementSize * elementCount;

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Width = totalSize;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		KE_ASSERT(!FAILED(device->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(&_resource))),
			"Failed to create structured buffer resource.");

		_descriptorHandle = heap.allocate();

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = elementCount;
		srvDesc.Buffer.StructureByteStride = elementSize;
		device->CreateShaderResourceView(_resource.Get(), &srvDesc, _descriptorHandle.cpuHandle);
	}

	void StructuredBufferResource::destroy()
	{
		if (_mappedData != nullptr)
		{
			unmap();
		}

		if (_heap != nullptr && _descriptorHandle.isValid())
		{
			_heap->release(_descriptorHandle);
			_descriptorHandle = {};
		}

		_resource.Reset();
		_heap = nullptr;
		_elementSize = 0;
		_elementCount = 0;
	}

	void* StructuredBufferResource::map()
	{
		KE_ASSERT(_resource != nullptr, "Resource is not initialized.");
		KE_ASSERT(_mappedData == nullptr, "Resource is already mapped.");

		D3D12_RANGE readRange = { 0, 0 };
		KE_ASSERT(!FAILED(_resource->Map(0, &readRange, &_mappedData)),
			"Failed to map structured buffer resource.");

		return _mappedData;
	}

	void StructuredBufferResource::unmap()
	{
		KE_ASSERT(_resource != nullptr, "Resource is not initialized.");
		KE_ASSERT(_mappedData != nullptr, "Resource is not mapped.");

		_resource->Unmap(0, nullptr);
		_mappedData = nullptr;
	}

	void StructuredBufferResource::upload(const void* data, uint32_t size)
	{
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= getTotalSize(), "Upload size exceeds buffer size.");

		void* mapped = map();
		memcpy(mapped, data, size);
		unmap();
	}
}
