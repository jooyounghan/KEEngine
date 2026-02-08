#include "GraphicsSystemPch.h"
#include "StructuredBuffer.h"

namespace ke
{
	StructuredBuffer::~StructuredBuffer()
	{
		shutdown();
	}

	void StructuredBuffer::initialize(
		ID3D12Device* device,
		uint32 elementCount,
		uint32 elementSize,
		bool cpuWritable,
		DescriptorHeap* srvHeap)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(elementCount > 0, "Element count must be greater than zero.");
		KE_ASSERT(elementSize > 0, "Element size must be greater than zero.");

		_elementCount = elementCount;
		_elementSize = elementSize;
		_cpuWritable = cpuWritable;

		const uint64 totalSize = static_cast<uint64>(elementCount) * elementSize;

		const D3D12_HEAP_PROPERTIES heapProps = {
			cpuWritable ? D3D12_HEAP_TYPE_UPLOAD : D3D12_HEAP_TYPE_DEFAULT
		};
		const D3D12_RESOURCE_DESC resourceDesc = {
			D3D12_RESOURCE_DIMENSION_BUFFER, 0,
			totalSize, 1, 1, 1,
			DXGI_FORMAT_UNKNOWN,
			{ 1, 0 },
			D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			D3D12_RESOURCE_FLAG_NONE
		};

		const D3D12_RESOURCE_STATES initialState = cpuWritable
			? D3D12_RESOURCE_STATE_GENERIC_READ
			: D3D12_RESOURCE_STATE_COMMON;

		KE_ASSERT(!FAILED(device->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initialState,
			nullptr, IID_PPV_ARGS(&_resource))),
			"Failed to create structured buffer resource.");

		if (srvHeap != nullptr)
		{
			_ownerHeap = srvHeap;
			_srvHandle = srvHeap->allocate();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = elementCount;
			srvDesc.Buffer.StructureByteStride = elementSize;
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

			device->CreateShaderResourceView(_resource.Get(), &srvDesc, _srvHandle.cpuHandle);
		}
	}

	void StructuredBuffer::shutdown()
	{
		if (_ownerHeap != nullptr && _srvHandle.isValid())
		{
			_ownerHeap->release(_srvHandle);
			_srvHandle = {};
			_ownerHeap = nullptr;
		}
		_resource.Reset();
		_elementCount = 0;
		_elementSize = 0;
	}

	void StructuredBuffer::upload(const void* data, uint32 size)
	{
		KE_ASSERT(_cpuWritable, "Cannot upload to a GPU-only structured buffer. Use CopyCommandContext instead.");
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= getBufferSize(), "Upload size exceeds buffer capacity.");

		void* mapped = map();
		memcpy(mapped, data, size);
		unmap();
	}
}
