#include "GraphicsSystemPch.h"
#include "StructuredBuffer.h"
#include "CommandContext.h"

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
		DescriptorHeap* srvHeap)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(elementCount > 0, "Element count must be greater than zero.");
		KE_ASSERT(elementSize > 0, "Element size must be greater than zero.");

		_elementCount = elementCount;
		_elementSize = elementSize;

		const uint64 totalSize = static_cast<uint64>(elementCount) * elementSize;

		// Create DEFAULT-heap resource (GPU-only, externally visible)
		{
			const D3D12_HEAP_PROPERTIES heapProps = {
				D3D12_HEAP_TYPE_DEFAULT,
				D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
				D3D12_MEMORY_POOL_UNKNOWN, 0, 0
			};
			const D3D12_RESOURCE_DESC resourceDesc = {
				D3D12_RESOURCE_DIMENSION_BUFFER, 0,
				totalSize, 1, 1, 1,
				DXGI_FORMAT_UNKNOWN,
				{ 1, 0 },
				D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
				D3D12_RESOURCE_FLAG_NONE
			};

			KE_ASSERT(!FAILED(device->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE,
				&resourceDesc, D3D12_RESOURCE_STATE_COMMON,
				nullptr, IID_PPV_ARGS(&_resource))),
				"Failed to create structured buffer default resource.");
		}

		// Create UPLOAD-heap staging resource
		{
			const D3D12_HEAP_PROPERTIES heapProps = {
				D3D12_HEAP_TYPE_UPLOAD,
				D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
				D3D12_MEMORY_POOL_UNKNOWN, 0, 0
			};
			const D3D12_RESOURCE_DESC resourceDesc = {
				D3D12_RESOURCE_DIMENSION_BUFFER, 0,
				totalSize, 1, 1, 1,
				DXGI_FORMAT_UNKNOWN,
				{ 1, 0 },
				D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
				D3D12_RESOURCE_FLAG_NONE
			};

			KE_ASSERT(!FAILED(device->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE,
				&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr, IID_PPV_ARGS(&_stagingResource))),
				"Failed to create structured buffer staging resource.");
		}

		if (srvHeap != nullptr)
		{
			_ownerHeap = srvHeap;
			_descriptorHandle = srvHeap->allocate();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = elementCount;
			srvDesc.Buffer.StructureByteStride = elementSize;
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

			device->CreateShaderResourceView(_resource.Get(), &srvDesc, _descriptorHandle.cpuHandle);
		}
	}

	void StructuredBuffer::shutdown()
	{
		releaseDescriptor();
		_stagingResource.Reset();
		_resource.Reset();
		_elementCount = 0;
		_elementSize = 0;
	}

	void StructuredBuffer::upload(const void* data, uint32 size)
	{
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= getBufferSize(), "Upload size exceeds buffer capacity.");

		void* mappedData = nullptr;
		D3D12_RANGE readRange = { 0, 0 };
		KE_ASSERT(!FAILED(_stagingResource->Map(0, &readRange, &mappedData)),
			"Failed to map staging resource.");

		memcpy(mappedData, data, size);
		_stagingResource->Unmap(0, nullptr);
	}

	void StructuredBuffer::commitUpload(CopyCommandContext& copyCtx)
	{
		KE_ASSERT(_resource, "Default resource is not initialized.");
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");

		const uint64 totalSize = static_cast<uint64>(_elementCount) * _elementSize;
		copyCtx.copyBufferRegion(
			_resource.Get(), 0,
			_stagingResource.Get(), 0,
			totalSize);
	}
}
