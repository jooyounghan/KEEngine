#pragma once

namespace ke
{
	class SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		void initialize(
			Microsoft::WRL::ComPtr<ID3D12Device> device,
			Microsoft::WRL::ComPtr<IDXGIFactory4> factory,
			Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue,
			HWND hwnd,
			int width,
			int height
		);

		void resize(int width, int height);
		void present();
		void waitForGpu();

		Microsoft::WRL::ComPtr<ID3D12Resource> getCurrentBackBuffer() const;
		D3D12_CPU_DESCRIPTOR_HANDLE getCurrentBackBufferRTV() const;
		UINT getCurrentBackBufferIndex() const { return _currentBackBufferIndex; }

	private:
		void updateRenderTargets();

	private:
		static const UINT BufferCount = 2;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain3> _swapChain;
		Microsoft::WRL::ComPtr<ID3D12Device> _device;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource> _renderTargets[BufferCount];

		UINT _rtvDescriptorSize;
		UINT _currentBackBufferIndex;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> _commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence> _fence;

		int _width;
		int _height;
		UINT64 _fenceValue;
		HANDLE _fenceEvent;
	};
}
