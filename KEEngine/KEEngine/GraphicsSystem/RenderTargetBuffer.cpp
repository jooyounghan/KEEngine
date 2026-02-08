#include "GraphicsSystemPch.h"
#include "RenderTargetBuffer.h"

namespace ke
{
	RenderTargetBuffer::~RenderTargetBuffer()
	{
		shutdown();
	}

	void RenderTargetBuffer::initialize(
		ID3D12Device* device,
		uint32 width, uint32 height,
		DXGI_FORMAT format,
		DescriptorHeap* rtvHeap,
		const float* clearColor)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(rtvHeap != nullptr, "RTV heap must not be null.");
		KE_ASSERT(width > 0 && height > 0, "Render target dimensions must be greater than zero.");

		_width = width;
		_height = height;
		_format = format;
		_ownerHeap = rtvHeap;

		D3D12_CLEAR_VALUE optimizedClearValue = {};
		optimizedClearValue.Format = format;
		if (clearColor)
		{
			optimizedClearValue.Color[0] = clearColor[0];
			optimizedClearValue.Color[1] = clearColor[1];
			optimizedClearValue.Color[2] = clearColor[2];
			optimizedClearValue.Color[3] = clearColor[3];
		}

		const D3D12_HEAP_PROPERTIES heapProps = { D3D12_HEAP_TYPE_DEFAULT };
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Width = width;
		resourceDesc.Height = height;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = format;
		resourceDesc.SampleDesc = { 1, 0 };
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		KE_ASSERT(!FAILED(device->CreateCommittedResource(
			&heapProps, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_RENDER_TARGET,
			&optimizedClearValue, IID_PPV_ARGS(&_resource))),
			"Failed to create render target resource.");

		_rtvHandle = rtvHeap->allocate();

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = format;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		device->CreateRenderTargetView(_resource.Get(), &rtvDesc, _rtvHandle.cpuHandle);
	}

	void RenderTargetBuffer::initializeFromSwapChain(
		ID3D12Device* device,
		ID3D12Resource* backBuffer,
		DescriptorHeap* rtvHeap)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(backBuffer != nullptr, "Back buffer must not be null.");
		KE_ASSERT(rtvHeap != nullptr, "RTV heap must not be null.");

		_ownerHeap = rtvHeap;
		backBuffer->AddRef();
		_resource.Attach(backBuffer);

		const D3D12_RESOURCE_DESC desc = backBuffer->GetDesc();
		_width = static_cast<uint32>(desc.Width);
		_height = desc.Height;
		_format = desc.Format;

		_rtvHandle = rtvHeap->allocate();
		device->CreateRenderTargetView(backBuffer, nullptr, _rtvHandle.cpuHandle);
	}

	void RenderTargetBuffer::shutdown()
	{
		if (_ownerHeap != nullptr && _rtvHandle.isValid())
		{
			_ownerHeap->release(_rtvHandle);
			_rtvHandle = {};
			_ownerHeap = nullptr;
		}
		_resource.Reset();
		_width = 0;
		_height = 0;
		_format = DXGI_FORMAT_UNKNOWN;
	}
}
