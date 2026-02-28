#include "GraphicsSystemPch.h"
#include "KEAppBase.h"
#include "DeviceManager.h"

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
		DeviceManager::getInstance().initialize();
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
}

