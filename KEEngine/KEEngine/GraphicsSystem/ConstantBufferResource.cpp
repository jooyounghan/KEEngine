#include "GraphicsSystemPch.h"
#include "ConstantBufferResource.h"

namespace ke
{
	ConstantBufferResource::~ConstantBufferResource()
	{
		destroy();
	}

	void ConstantBufferResource::init(ID3D12Device* device, DescriptorHeap& heap, uint32_t bufferSize)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(bufferSize > 0, "Buffer size must be greater than 0.");

		_heap = &heap;
		_bufferSize = (bufferSize + 255) & ~255;

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Width = _bufferSize;
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
			"Failed to create constant buffer resource.");

		_descriptorHandle = heap.allocate();

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = _resource->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = _bufferSize;
		device->CreateConstantBufferView(&cbvDesc, _descriptorHandle.cpuHandle);
	}

	void ConstantBufferResource::destroy()
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
		_bufferSize = 0;
	}

	void* ConstantBufferResource::map()
	{
		KE_ASSERT(_resource != nullptr, "Resource is not initialized.");
		KE_ASSERT(_mappedData == nullptr, "Resource is already mapped.");

		D3D12_RANGE readRange = { 0, 0 };
		KE_ASSERT(!FAILED(_resource->Map(0, &readRange, &_mappedData)),
			"Failed to map constant buffer resource.");

		return _mappedData;
	}

	void ConstantBufferResource::unmap()
	{
		KE_ASSERT(_resource != nullptr, "Resource is not initialized.");
		KE_ASSERT(_mappedData != nullptr, "Resource is not mapped.");

		_resource->Unmap(0, nullptr);
		_mappedData = nullptr;
	}

	void ConstantBufferResource::upload(const void* data, uint32_t size)
	{
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= _bufferSize, "Upload size exceeds buffer size.");

		void* mapped = map();
		memcpy(mapped, data, size);
		unmap();
	}
}
