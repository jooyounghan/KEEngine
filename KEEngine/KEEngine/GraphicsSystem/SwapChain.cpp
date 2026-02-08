#include "GraphicsSystemPch.h"
#include "SwapChain.h"

namespace ke
{
	SwapChain::SwapChain()
		: _rtvDescriptorSize(0)
		, _currentBackBufferIndex(0)
		, _fenceValue(0)
		, _fenceEvent(nullptr)
		, _width(0)
		, _height(0)
	{
	}

	SwapChain::~SwapChain()
	{
		if (_fenceEvent)
		{
			CloseHandle(_fenceEvent);
			_fenceEvent = nullptr;
		}
	}

	void SwapChain::initialize(
		Microsoft::WRL::ComPtr<ID3D12Device> device,
		Microsoft::WRL::ComPtr<IDXGIFactory4> factory,
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue,
		HWND hwnd,
		int width,
		int height)
	{
		_device = device;
		_commandQueue = commandQueue;
		_width = width;
		_height = height;

		_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));
		_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.BufferCount = BufferCount;
		swapChainDesc.Width = width;
		swapChainDesc.Height = height;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		factory->CreateSwapChainForHwnd(
			commandQueue.Get(),
			hwnd,
			&swapChainDesc,
			nullptr,
			nullptr,
			&swapChain
		);

		factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

		swapChain.As(&_swapChain);
		_currentBackBufferIndex = _swapChain->GetCurrentBackBufferIndex();

		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = BufferCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&_rtvHeap));
		_rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		updateRenderTargets();
	}

	void SwapChain::resize(int width, int height)
	{
		if (_width == width && _height == height)
			return;

		waitForGpu();

		_width = width;
		_height = height;

		for (UINT i = 0; i < BufferCount; ++i)
		{
			_renderTargets[i].Reset();
		}

		DXGI_SWAP_CHAIN_DESC desc = {};
		_swapChain->GetDesc(&desc);

		_swapChain->ResizeBuffers(
			BufferCount,
			width,
			height,
			desc.BufferDesc.Format,
			desc.Flags
		);

		_currentBackBufferIndex = _swapChain->GetCurrentBackBufferIndex();

		updateRenderTargets();
	}

	void SwapChain::updateRenderTargets()
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

		for (UINT i = 0; i < BufferCount; ++i)
		{
			_swapChain->GetBuffer(i, IID_PPV_ARGS(&_renderTargets[i]));
			_device->CreateRenderTargetView(_renderTargets[i].Get(), nullptr, rtvHandle);
			rtvHandle.ptr += _rtvDescriptorSize;
		}
	}

	void SwapChain::present()
	{
		_swapChain->Present(1, 0);
		_currentBackBufferIndex = _swapChain->GetCurrentBackBufferIndex();
	}

	void SwapChain::waitForGpu()
	{
		_fenceValue++;
		_commandQueue->Signal(_fence.Get(), _fenceValue);

		if (_fence->GetCompletedValue() < _fenceValue)
		{
			_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);
			WaitForSingleObject(_fenceEvent, INFINITE);
		}
	}

	Microsoft::WRL::ComPtr<ID3D12Resource> SwapChain::getCurrentBackBuffer() const
	{
		return _renderTargets[_currentBackBufferIndex];
	}

	D3D12_CPU_DESCRIPTOR_HANDLE SwapChain::getCurrentBackBufferRTV() const
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
		handle.ptr += static_cast<SIZE_T>(_currentBackBufferIndex) * _rtvDescriptorSize;
		return handle;
	}
}
