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

    public:
        int run();

    protected:
        virtual void onInit();
        virtual void onUpdate(float dt) = 0;
		virtual void onRender() = 0;
        virtual void onDestroy() = 0;
  
    public:
        LRESULT WINAPI appProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };
}