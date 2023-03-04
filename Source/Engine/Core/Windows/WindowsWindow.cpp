#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsPlatform.h>



#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

namespace GeometricEngine
{
	static bool HasClosed = false;
    WindowsWindow::WindowsWindow(const WindowDefinition& Definition)
    {

		DWORD StyleEx = 0, Style = 0;
		I32 X = static_cast<I32>(Definition.PositionX);
		I32 Y = static_cast<I32>(Definition.PositionX);
		I32 Width = static_cast<I32>(Definition.SizeWidth);
		I32 Height = static_cast<I32>(Definition.SizeHeight);

		if(Definition.HasWindowBorder)
		{
			StyleEx = WS_EX_APPWINDOW;
			Style = WS_POPUP | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_BORDER | WS_CAPTION;
			RECT WindowRect = { 0, 0, Width, Height };
			AdjustWindowRectEx(&WindowRect, Style, false, StyleEx);
			X += WindowRect.left;
			Y += WindowRect.top;
			Width = WindowRect.right - WindowRect.left;
			Height = WindowRect.bottom - WindowRect.top;
		}
		else
		{

		}

        HandleWindow = CreateWindowEx(	StyleEx,
										TEXT("GeometricEngine"), 
										Definition.Title.Pointer(),
										Style,
										X, Y,
										Width, 
										Height,
										NULL, 
										NULL, 
										WindowsPlatform::HandleInstance,
										this);


		Show();


    }
    WindowsWindow::~WindowsWindow()
    {
        if(HandleWindow)
            DestroyWindow(HandleWindow);
    }
    bool WindowsWindow::IsOpen()
    {
        return !HasClosed;
    }
	bool WindowsWindow::IsClose()
	{
		return HasClosed;
	}
    void WindowsWindow::Close()
    {
		HasClosed = true;
		HandleWindow = NULL;
    }
    void WindowsWindow::Show()
    {
        ShowWindow(HandleWindow, SW_SHOW);
    }
    void WindowsWindow::Hide()
    {
        ShowWindow(HandleWindow, SW_HIDE);
    }
    void WindowsWindow::SetPosition(const Vector2i& position)
    {
        SetWindowPos(HandleWindow, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
    void WindowsWindow::SetSize(const Vector2u& size)
    {
        RECT rectangle = {0, 0, static_cast<long>(size.x), static_cast<long>(size.y)};
        AdjustWindowRect(&rectangle, GetWindowLong(HandleWindow, GWL_STYLE), false);
        int width  = rectangle.right - rectangle.left;
        int height = rectangle.bottom - rectangle.top;
        SetWindowPos(HandleWindow, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    }
    void WindowsWindow::SetTitle(const StringView& Title)
    {
        SetWindowText(HandleWindow, Title.Pointer());
    }

    Vector2u WindowsWindow::GetSize() const
    {
        RECT rect;
        GetClientRect(HandleWindow, &rect);
        return Vector2u(rect.right - rect.left, rect.bottom - rect.top);
    }
    Vector2i WindowsWindow::GetPosition() const
    {
        RECT rect;
        GetWindowRect(HandleWindow, &rect);
        return Vector2i(rect.left, rect.top);
    }
    void* WindowsWindow::GetHandle() const
    {
        return HandleWindow;
    }

	void WindowsWindow::WndProc(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_CLOSE:
            {
				HasClosed = true;
				break;
            }
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return;
			}
        }
    }

}
