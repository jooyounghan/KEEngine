#include "GraphicsSystemPch.h"
#include "Texture3DResource.h"
#include "CommandContext.h"

namespace ke
{
	Texture3DResource::~Texture3DResource()
	{
		shutdown();
	}

	void Texture3DResource::initialize(
		ID3D12Device* device,
		uint32 width,
		uint32 height,
		uint16 depth,
		DXGI_FORMAT format,
		DescriptorHeap* srvHeap,
		uint16 mipLevels)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(width > 0 && height > 0 && depth > 0, "Texture dimensions must be greater than zero.");

		_width = width;
		_height = height;
		_depth = depth;
		_format = format;
		_mipLevels = mipLevels;

		// Create DEFAULT-heap 3D texture
		{
			const D3D12_HEAP_PROPERTIES heapProps = { D3D12_HEAP_TYPE_DEFAULT };
			D3D12_RESOURCE_DESC resourceDesc = {};
			resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
			resourceDesc.Width = width;
			resourceDesc.Height = height;
			resourceDesc.DepthOrArraySize = depth;
			resourceDesc.MipLevels = mipLevels;
			resourceDesc.Format = format;
			resourceDesc.SampleDesc = { 1, 0 };
			resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			KE_ASSERT(!FAILED(device->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE,
				&resourceDesc, D3D12_RESOURCE_STATE_COMMON,
				nullptr, IID_PPV_ARGS(&_resource))),
				"Failed to create 3D texture default resource.");
		}

		// Query required staging size via GetCopyableFootprints
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
		uint64 totalBytes = 0;
		{
			const D3D12_RESOURCE_DESC texDesc = _resource->GetDesc();
			device->GetCopyableFootprints(&texDesc, 0, 1, 0, &footprint, nullptr, nullptr, &totalBytes);
			_rowPitch = footprint.Footprint.RowPitch;
			_slicePitch = _rowPitch * footprint.Footprint.Height;
		}

		// Create UPLOAD-heap staging buffer
		{
			const D3D12_HEAP_PROPERTIES heapProps = { D3D12_HEAP_TYPE_UPLOAD };
			const D3D12_RESOURCE_DESC bufferDesc = {
				D3D12_RESOURCE_DIMENSION_BUFFER, 0,
				totalBytes, 1, 1, 1,
				DXGI_FORMAT_UNKNOWN,
				{ 1, 0 },
				D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
				D3D12_RESOURCE_FLAG_NONE
			};

			KE_ASSERT(!FAILED(device->CreateCommittedResource(
				&heapProps, D3D12_HEAP_FLAG_NONE,
				&bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr, IID_PPV_ARGS(&_stagingResource))),
				"Failed to create 3D texture staging resource.");
		}

		// Create SRV if heap is provided
		if (srvHeap != nullptr)
		{
			_ownerHeap = srvHeap;
			_descriptorHandle = srvHeap->allocate();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format = format;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Texture3D.MostDetailedMip = 0;
			srvDesc.Texture3D.MipLevels = mipLevels;
			srvDesc.Texture3D.ResourceMinLODClamp = 0.0f;

			device->CreateShaderResourceView(_resource.Get(), &srvDesc, _descriptorHandle.cpuHandle);
		}
	}

	void Texture3DResource::shutdown()
	{
		releaseDescriptor();
		_stagingResource.Reset();
		_resource.Reset();
		_width = 0;
		_height = 0;
		_depth = 0;
		_format = DXGI_FORMAT_UNKNOWN;
		_mipLevels = 1;
		_rowPitch = 0;
		_slicePitch = 0;
	}

	void Texture3DResource::upload(const void* data, uint32 size)
	{
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");
		KE_ASSERT(data != nullptr, "Data must not be null.");

		void* mappedData = nullptr;
		D3D12_RANGE readRange = { 0, 0 };
		KE_ASSERT(!FAILED(_stagingResource->Map(0, &readRange, &mappedData)),
			"Failed to map staging resource.");

		memcpy(mappedData, data, size);
		_stagingResource->Unmap(0, nullptr);
	}

	void Texture3DResource::commitUpload(CopyCommandContext& copyCtx)
	{
		KE_ASSERT(_resource, "Default resource is not initialized.");
		KE_ASSERT(_stagingResource, "Staging resource is not initialized.");

		D3D12_TEXTURE_COPY_LOCATION dst = {};
		dst.pResource = _resource.Get();
		dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex = 0;

		D3D12_TEXTURE_COPY_LOCATION src = {};
		src.pResource = _stagingResource.Get();
		src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset = 0;
		src.PlacedFootprint.Footprint.Format = _format;
		src.PlacedFootprint.Footprint.Width = _width;
		src.PlacedFootprint.Footprint.Height = _height;
		src.PlacedFootprint.Footprint.Depth = _depth;
		src.PlacedFootprint.Footprint.RowPitch = _rowPitch;

		copyCtx.copyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
	}
}
