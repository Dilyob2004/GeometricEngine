#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsPlatform.h>



#include <dwmapi.h>

/**#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif
#ifndef XBUTTON1
    #define XBUTTON1 0x0001
#endif
#ifndef XBUTTON2
    #define XBUTTON2 0x0002
#endif
#ifndef WM_MOUSEHWHEEL
    #define WM_MOUSEHWHEEL 0x020E
#endif
*/
namespace GeometricEngine
{
    WindowsWindow::WindowsWindow(const std::string& title, const Vector2u& size)
    {
        RECT rect;
		rect.right = size.x;
		rect.bottom = size.y;

		rect.left = GetSystemMetrics(SM_CXSCREEN) / 2  - rect.right/2;
		rect.top = GetSystemMetrics(SM_CYSCREEN) / 2 - rect.bottom/2;
		
        DWORD styleEx = WS_EX_APPWINDOW,  style = WS_OVERLAPPEDWINDOW;
		AdjustWindowRectEx(&rect, style, false, styleEx);
        m_hwnd = CreateWindowExA(	styleEx,	
									TEXT("MeteorEngine"), title.c_str(),
									style,
									rect.left, rect.top,
									rect.right, rect.bottom,
									NULL, NULL, 
									WindowsPlatform::HandleInstance,
									this);


		Show();


    }
    WindowsWindow::~WindowsWindow()
    {
        if(m_hwnd)
            DestroyWindow(m_hwnd);
    }
    bool WindowsWindow::IsOpen()
    {
        return m_hwnd != NULL;
    }
    void WindowsWindow::Quit()
    {
        m_hwnd = NULL;
    }
    void WindowsWindow::Show()
    {
        ShowWindow(m_hwnd, SW_SHOW);
    }
    void WindowsWindow::Hide()
    {
        ShowWindow(m_hwnd, SW_HIDE);
    }
    void WindowsWindow::SetPosition(const Vector2i& position)
    {
        SetWindowPos(m_hwnd, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
    void WindowsWindow::SetSize(const Vector2u& size)
    {
        RECT rectangle = {0, 0, static_cast<long>(size.x), static_cast<long>(size.y)};
        AdjustWindowRect(&rectangle, GetWindowLong(m_hwnd, GWL_STYLE), false);
        int width  = rectangle.right - rectangle.left;
        int height = rectangle.bottom - rectangle.top;
        SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    }
    void WindowsWindow::SetTitle(const std::string& title)
    {
        SetWindowText(m_hwnd, title.c_str());
    }

    Vector2u WindowsWindow::GetSize() const
    {
        RECT rect;
        GetClientRect(m_hwnd, &rect);
        return Vector2u(rect.right - rect.left, rect.bottom - rect.top);
    }
    Vector2i WindowsWindow::GetPosition() const
    {
        RECT rect;
        GetWindowRect(m_hwnd, &rect);
        return Vector2i(rect.left, rect.top);
    }
    void* WindowsWindow::GetWindowPtr() const
    {
        return m_hwnd;
    }

    /**void WindowsWindow::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_CLOSE:
            {
            }
        }

    }*/

}
