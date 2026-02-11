#include "GraphicsSystemPch.h"
#include "ConstantBuffer.h"
#include "CommandContext.h"
#include "MemoryUtil.h"

namespace ke
{
	ConstantBuffer::~ConstantBuffer()
	{
		shutdown();
	}

	void ConstantBuffer::initialize(ID3D12Device* device, uint32 bufferSize, DescriptorHeap* cbvHeap)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(bufferSize > 0, "Buffer size must be greater than zero.");

		_bufferSize = static_cast<uint32>(MemoryUtil::getAlignedUp(bufferSize, 256));

		// Create DEFAULT-heap resource (GPU-only, externally visible)
		{
			const D3D12_HEAP_PROPERTIES heapProps = { D3D12_HEAP_TYPE_DEFAULT };
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
				&resourceDesc, D3D12_RESOURCE_STATE_COMMON,
				nullptr, IID_PPV_ARGS(&_resource))),
				"Failed to create constant buffer default resource.");
		}

		// Create UPLOAD-heap staging resource
		{
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
				nullptr, IID_PPV_ARGS(&_stagingResource))),
				"Failed to create constant buffer staging resource.");
		}

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
		releaseDescriptor();
		_stagingResource.Reset();
		_resource.Reset();
		_bufferSize = 0;
	}

	void ConstantBuffer::upload(const void* data, uint32 size)
	{
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");
		KE_ASSERT(data != nullptr, "Data must not be null.");
		KE_ASSERT(size <= _bufferSize, "Upload size exceeds buffer capacity.");

		void* mappedData = nullptr;
		D3D12_RANGE readRange = { 0, 0 };
		KE_ASSERT(!FAILED(_stagingResource->Map(0, &readRange, &mappedData)),
			"Failed to map staging resource.");

		memcpy(mappedData, data, size);
		_stagingResource->Unmap(0, nullptr);
	}

	void ConstantBuffer::commitUpload(CopyCommandContext& copyCtx)
	{
		KE_ASSERT(_resource, "Default resource is not initialized.");
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");

		copyCtx.copyBufferRegion(
			_resource.Get(), 0,
			_stagingResource.Get(), 0,
			_bufferSize);
	}
}
