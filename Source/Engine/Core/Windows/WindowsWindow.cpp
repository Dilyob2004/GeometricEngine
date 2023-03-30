#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/Log.h>
#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

namespace GeometricEngine
{
    WindowsWindow::WindowsWindow(const WindowDefinition& Definition)
    {
        HandleIcon = NULL;
		DWORD StyleEx = 0, Style = 0;
		I32 X = static_cast<I32>(Definition.PositionX);
		I32 Y = static_cast<I32>(Definition.PositionX);
		I32 Width = static_cast<I32>(Definition.SizeWidth);
		I32 Height = static_cast<I32>(Definition.SizeHeight);

		if(Definition.HasBorder)
		{
           // StyleEx = WS_EX_APPWINDOW;
            Style = WS_OVERLAPPEDWINDOW;
            RECT WindowRect = { 0, 0, Width, Height };
            AdjustWindowRectEx(&WindowRect, Style, false, StyleEx);
            X += WindowRect.left;
            Y += WindowRect.top;
            Width = WindowRect.right - WindowRect.left;
            Height = WindowRect.bottom - WindowRect.top;
		}
		else
		{
            StyleEx = WS_EX_WINDOWEDGE;
            Style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
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


        ShowWindow(HandleWindow, SW_SHOW);
        UpdateWindow(HandleWindow);

    }
    WindowsWindow::~WindowsWindow()
    {
        if (HandleIcon)
            DestroyIcon(HandleIcon);
        if(HandleWindow)
            DestroyWindow(HandleWindow);
    }
    bool WindowsWindow::IsOpen()
    {
        return HandleWindow != NULL;
    }
    void WindowsWindow::Close()
    {
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
    void WindowsWindow::SetIcon(const TVector<U8>& Data, U32 Width, U32 Height)
    {
        if (HandleIcon)
            DestroyIcon(HandleIcon);

        U8* NewData = new U8[Width * Height * 4];
        for (I32 i = 0; i < Width * Height; i++)
        {
            NewData[i * 4 + 0] = Data[i * 4 + 2];
            NewData[i * 4 + 1] = Data[i * 4 + 1];
            NewData[i * 4 + 2] = Data[i * 4 + 0];
            NewData[i * 4 + 3] = Data[i * 4 + 3];
        }
        HandleIcon = CreateIcon(WindowsPlatform::HandleInstance,
                                Width, Height, 1, 32, NULL, NewData);
        if (HandleIcon) 
        {
            SendMessage(HandleWindow, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(HandleIcon));
            SendMessage(HandleWindow, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(HandleIcon));
        }
        else
            LOG("Warning: [ICON] Failed to set icon!");
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
	U32 WindowsWindow::GetWidth() const
	{
		RECT rect;
		GetClientRect(HandleWindow, &rect);
		return rect.right - rect.left;
	}
	U32 WindowsWindow::GetHeight() const
	{
		RECT rect;
		GetClientRect(HandleWindow, &rect);
		return rect.bottom - rect.top;
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

}
