#include "GraphicsSystemPch.h"
#include "KEAppBase.h"

using namespace Microsoft::WRL;

namespace ke
{
	KEAppBase* KEAppBase::gKEAppBase = nullptr;

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return KEAppBase::gKEAppBase->appProc(hWnd, msg, wParam, lParam);
	}

	KEAppBase::KEAppBase(int width, int height, const wchar_t* className, const wchar_t* appName)
	{
		gKEAppBase = this;

		memset(&_windowClass, 0, sizeof(_windowClass));
		_windowClass =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, WndProc,
			0L, 0L, GetModuleHandle(nullptr),
			nullptr, nullptr, nullptr,
			nullptr, className, nullptr
		};
		RegisterClassEx(&_windowClass);

		HWND hWindow = CreateWindow(
			_windowClass.lpszClassName, appName,
			WS_OVERLAPPEDWINDOW, 0, 0,
			width, height, nullptr,
			nullptr, _windowClass.hInstance, nullptr
		);
		_windowHandle = hWindow;
	}

	int KEAppBase::run()
	{
		onInit();

		ShowWindow(_windowHandle, SW_SHOWDEFAULT);

		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			// Process any messages in the queue.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				const float deltaTime = _timer.getMeasuredTime();
				_timer.refreshClock();
				onUpdate(deltaTime);
				onRender();
			}
		}

		onDestroy();
		return static_cast<char>(msg.wParam);
	}

	void KEAppBase::onInit()
	{
		_timer.startClock();

#if defined(_DEBUG)
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
#endif

		KE_ASSERT(!FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&_factory))), "Failed to create DXGI Factory and D3D12 Device.");
		getHardwareAdapter(_factory.Get(), &_hardwareAdapter);

		KE_ASSERT(!FAILED(D3D12CreateDevice(
			_hardwareAdapter.Get(),
			D3D_FEATURE_LEVEL_12_2,
			IID_PPV_ARGS(&_device)
		)), "Failed to create D3D12 Device.");
	}

	LRESULT __stdcall KEAppBase::appProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		}
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// ==============================================================================================
	// From DirectX12 Example https://github.com/microsoft/DirectX-Graphics-Samples 
	void KEAppBase::getHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter)
	{
		*ppAdapter = nullptr;

		ComPtr<IDXGIAdapter1> adapter;

		ComPtr<IDXGIFactory6> factory6;
		if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6))))
		{
			for (
				UINT adapterIndex = 0;
				SUCCEEDED(factory6->EnumAdapterByGpuPreference(
					adapterIndex,
					requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED,
					IID_PPV_ARGS(&adapter)));
					++adapterIndex)
			{
				DXGI_ADAPTER_DESC1 desc;
				adapter->GetDesc1(&desc);

				if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
					// Don't select the Basic Render Driver adapter.
					// If you want a software adapter, pass in "/warp" on the command line.
					continue;
				}

				// Check to see whether the adapter supports Direct3D 12, but don't create the
				// actual device yet.
				if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, _uuidof(ID3D12Device), nullptr)))
				{
					break;
				}
			}
		}

		if (adapter.Get() == nullptr)
		{
			for (UINT adapterIndex = 0; SUCCEEDED(pFactory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
			{
				DXGI_ADAPTER_DESC1 desc;
				adapter->GetDesc1(&desc);

				if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				{
					// Don't select the Basic Render Driver adapter.
					// If you want a software adapter, pass in "/warp" on the command line.
					continue;
				}

				// Check to see whether the adapter supports Direct3D 12, but don't create the
				// actual device yet.
				if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, _uuidof(ID3D12Device), nullptr)))
				{
					break;
				}
			}
		}

		*ppAdapter = adapter.Detach();
	}
	// ==============================================================================================
}

