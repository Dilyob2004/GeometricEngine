#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Misc/Log.h>
WindowsWindow::WindowsWindow(const WindowDefinition& Def)
    : Definition(Def)
    , RegionWidth(-1)
    , RegionHeight(-1)
    , HandleIcon(NULL)
{
	DWORD StyleEx = 0, Style = 0;

    HDC HandleDevice = GetDC(NULL);
    I32 Width = static_cast<I32>(Definition.SizeWidth);
    I32 Height = static_cast<I32>(Definition.SizeHeight);
	I32 X = (GetDeviceCaps(HandleDevice, HORZRES) - Width) / 2;
	I32 Y = (GetDeviceCaps(HandleDevice, VERTRES) - Height) / 2;
    ReleaseDC(NULL, HandleDevice);


    if (!Definition.Fullscreen) 
    {
        StyleEx = WS_EX_APPWINDOW;
        Style = WS_OVERLAPPEDWINDOW;
        RECT WindowRect = { 0, 0, Width, Height };
        AdjustWindowRectEx(&WindowRect, Style, false, StyleEx);
        Width = WindowRect.right - WindowRect.left;
        Height = WindowRect.bottom - WindowRect.top;
    }

    HandleWindow = CreateWindowEx(	StyleEx,
									TEXT("GeometricEngine"), 
                                    *Definition.Title,
									Style,
									X, Y,
									Width, 
									Height,
									NULL, NULL, 
									WindowsPlatform::HandleInstance, NULL);
    if (Definition.Fullscreen)
    {
        DEVMODE Mode;
        SMemory::Zero(&Mode, sizeof(Mode));
        Mode.dmSize = sizeof(Mode);
        Mode.dmPelsWidth = Width;
        Mode.dmPelsHeight = Height;
        Mode.dmBitsPerPel = 32;
        Mode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
        if (ChangeDisplaySettings(&Mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            LOG("Error: [WINDOW] Failed to change display mode for fullscreen!\n");
            exit(-1);
        }

        StyleEx = WS_EX_APPWINDOW;
        Style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        SetWindowLongPtr(HandleWindow, GWL_STYLE, static_cast<LONG_PTR>(Style));
        SetWindowLongPtr(HandleWindow, GWL_EXSTYLE, static_cast<LONG_PTR>(StyleEx));
            
        SetWindowPos(HandleWindow, HWND_TOP, 0, 0, Width, Height, SWP_FRAMECHANGED);

    }
    ShowWindow(HandleWindow, SW_SHOW);
    UpdateWindow(HandleWindow);


}
WindowsWindow::~WindowsWindow()
{
    if (HandleIcon)
        DestroyIcon(HandleIcon), HandleIcon = NULL;
    if (HandleWindow)
        DestroyWindow(HandleWindow), HandleWindow = NULL;
}

bool WindowsWindow::IsMaximized() const
{
    bool Maximized = IsZoomed(HandleWindow);
    return Maximized;
}
bool WindowsWindow::IsOpen()
{
    return HandleWindow != NULL;
}
void WindowsWindow::Close()
{
	HandleWindow = NULL;
}

void  WindowsWindow::Restore()
{
    ShowWindow(HandleWindow, SW_RESTORE);
}
void  WindowsWindow::Maximized()
{
    ShowWindow(HandleWindow, SW_MAXIMIZE);
}
void  WindowsWindow::Minimized()
{
    ShowWindow(HandleWindow, SW_MINIMIZE);
}
void WindowsWindow::Show()
{
    ShowWindow(HandleWindow, SW_SHOW);
}
void WindowsWindow::Hide()
{
    ShowWindow(HandleWindow, SW_HIDE);
}
void WindowsWindow::SetIcon(const TArray<U8>& Data, U32 Width, U32 Height)
{
    if (HandleIcon)
        DestroyIcon(HandleIcon);

    U8* NewData = new U8[Width * Height * 4];
    for (U32 i = 0; i < Width * Height; i++)
    {
        NewData[i * 4 + 0] = Data[i * 4 + 2];
        NewData[i * 4 + 1] = Data[i * 4 + 1];
        NewData[i * 4 + 2] = Data[i * 4 + 0];
        NewData[i * 4 + 3] = Data[i * 4 + 3];
    }
    HandleIcon = CreateIcon(WindowsPlatform::HandleInstance, Width, Height, 1, 32, NULL, NewData);
    if (HandleIcon) 
    {
        SendMessage(HandleWindow, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(HandleIcon));
        SendMessage(HandleWindow, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(HandleIcon));
    }
    else
        LOG("Warning: [ICON] Failed to create icon!");
}
void WindowsWindow::SetPosition(const Vector2f& position)
{
    SetWindowPos(HandleWindow, NULL, (int)position.x, (int)position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
void WindowsWindow::SetSize(const Vector2f& size)
{
    RECT rectangle = {0, 0, static_cast<long>(size.x), static_cast<long>(size.y)};
    AdjustWindowRect(&rectangle, GetWindowLong(HandleWindow, GWL_STYLE), false);
    int width  = rectangle.right - rectangle.left;
    int height = rectangle.bottom - rectangle.top;
    SetWindowPos(HandleWindow, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}
void WindowsWindow::SetTitle(const String& Title)
{
    SetWindowText(HandleWindow, Title.Pointer());
}
I32 WindowsWindow::GetWindowBorderSize() const
{
    WINDOWINFO WindowInfo;
    SMemory::Zero(&WindowInfo, sizeof(WindowInfo));
    WindowInfo.cbSize = sizeof(WindowInfo);
    GetWindowInfo(HandleWindow, &WindowInfo);

    return WindowInfo.cxWindowBorders;
}
Vector2f WindowsWindow::GetSize() const
{
    RECT rect;
    GetClientRect(HandleWindow, &rect);
    return Vector2f((F32)rect.right - rect.left, (F32)rect.bottom - rect.top);
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
Vector2f WindowsWindow::GetPosition() const
{
    RECT rect;
    GetWindowRect(HandleWindow, &rect); 
    return Vector2f((F32)rect.left, (F32)rect.top);
}
void* WindowsWindow::GetHandle() const
{
    return HandleWindow;
}

