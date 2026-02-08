#include "GraphicsSystemPch.h"
#include "ConstantBuffer.h"

namespace ke
{
	namespace
	{
		inline uint32 alignTo256(uint32 size)
		{
			return (size + 255) & ~255;
		}
	}

	ConstantBuffer::~ConstantBuffer()
	{
		shutdown();
	}

	void ConstantBuffer::initialize(ID3D12Device* device, uint32 bufferSize, DescriptorHeap* cbvHeap)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(bufferSize > 0, "Buffer size must be greater than zero.");

		_bufferSize = alignTo256(bufferSize);

		const D3D12_HEAP_PROPERTIES heapProps = { D3D12_HEAP_TYPE_UPLOAD };
		const D3D12_RESOURCE_DESC resourceDesc = {
			D3D12_RESOURCE_DIMENSION_BUFFER, 0,
			_bufferSize, 1, 1, 1,
			DXGI_FORMAT_UNKNOWN,
			{ 1, 0 },
			D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			D3D12_RESOURCE_FLAG_NONE
		};

		KE_ASSERT(!FAILED(device->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(&_resource))),
			"Failed to create constant buffer resource.");

		if (cbvHeap != nullptr)
		{
			_ownerHeap = cbvHeap;
			_descriptorHandle = cbvHeap->allocate();

			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
			cbvDesc.BufferLocation = _resource->GetGPUVirtualAddress();
			cbvDesc.SizeInBytes = _bufferSize;

			device->CreateConstantBufferView(&cbvDesc, _descriptorHandle.cpuHandle);
		}
	}

	void ConstantBuffer::shutdown()
	{
		if (_ownerHeap != nullptr && _descriptorHandle.isValid())
		{
			_ownerHeap->release(_descriptorHandle);
			_descriptorHandle = {};
			_ownerHeap = nullptr;
		}
		_resource.Reset();
		_bufferSize = 0;
	}

	void ConstantBuffer::upload(const void* data, uint32 size)
	{
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= _bufferSize, "Upload size exceeds buffer capacity.");

		void* mapped = map();
		memcpy(mapped, data, size);
		unmap();
	}
}
