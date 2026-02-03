#pragma once
#include "Timer.h"

namespace ke
{
    class KEAppBase
    {
    public:
        KEAppBase(int width, int height, const wchar_t* className, const wchar_t* appName);
        virtual ~KEAppBase() = default;

    public:
        static KEAppBase* gKEAppBase;

    protected:
        WNDCLASSEX  _windowClass;
        HWND        _windowHandle;

    protected:
		Timer   _timer;

    protected:
        Microsoft::WRL::ComPtr<ID3D12Device>    _device;
        Microsoft::WRL::ComPtr<IDXGIFactory4>   _factory;
        Microsoft::WRL::ComPtr<IDXGIAdapter1>   _hardwareAdapter;

    public:
        inline ID3D12Device* getDevice() const { return _device.Get(); }
        inline IDXGIFactory* getFactory() const { return _factory.Get(); }

    public:
        int run();

    protected:
        virtual void onInit();
        virtual void onUpdate(float dt) = 0;
		virtual void onRender() = 0;
        virtual void onDestroy() = 0;
  
    public:
        LRESULT WINAPI appProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    protected:
        void getHardwareAdapter(
            IDXGIFactory1* pFactory,
            IDXGIAdapter1** ppAdapter,
            bool requestHighPerformanceAdapter = false);
    };
}