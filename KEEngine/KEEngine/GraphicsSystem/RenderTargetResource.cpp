#include "GraphicsSystemPch.h"
#include "RenderTargetResource.h"

namespace ke
{
	RenderTargetResource::~RenderTargetResource()
	{
		destroy();
	}

	void RenderTargetResource::init(
		ID3D12Device* device,
		DescriptorHeap& heap,
		uint32_t width,
		uint32_t height,
		DXGI_FORMAT format)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(width > 0 && height > 0, "Width and height must be greater than 0.");

		_heap = &heap;
		_ownsResource = true;

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Width = width;
		resourceDesc.Height = height;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = format;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Format = format;
		clearValue.Color[0] = 0.0f;
		clearValue.Color[1] = 0.0f;
		clearValue.Color[2] = 0.0f;
		clearValue.Color[3] = 1.0f;

		KE_ASSERT(!FAILED(device->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_RENDER_TARGET,
			&clearValue, IID_PPV_ARGS(&_resource))),
			"Failed to create render target resource.");

		_descriptorHandle = heap.allocate();
		device->CreateRenderTargetView(_resource.Get(), nullptr, _descriptorHandle.cpuHandle);
	}

	void RenderTargetResource::initFromSwapChain(
		ID3D12Device* device,
		DescriptorHeap& heap,
		ID3D12Resource* swapChainBuffer)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(swapChainBuffer != nullptr, "Swap chain buffer must not be null.");

		_heap = &heap;
		_ownsResource = false;
		_resource = swapChainBuffer;

		_descriptorHandle = heap.allocate();
		device->CreateRenderTargetView(swapChainBuffer, nullptr, _descriptorHandle.cpuHandle);
	}

	void RenderTargetResource::destroy()
	{
		if (_heap != nullptr && _descriptorHandle.isValid())
		{
			_heap->release(_descriptorHandle);
			_descriptorHandle = {};
		}

		if (_ownsResource)
		{
			_resource.Reset();
		}
		else
		{
			_resource.Detach();
		}

		_heap = nullptr;
		_ownsResource = false;
	}
}
