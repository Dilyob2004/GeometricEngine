#include <ImGui/imgui.h>
#include <Engine/Platform/Win32/WindowsWindow.h>
#include <Engine/Core/MouseCodes.h>
#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
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

namespace MeteorEngine
{
	void SetHighDpiAwarenessEnabled(bool enable)
	{
		const HMODULE shCoreDll = LoadLibraryW(L"Shcore.dll");
		if (!shCoreDll)
			return;
		typedef enum _PROCESS_DPI_AWARENESS
		{
			PROCESS_DPI_UNAWARE = 0,
			PROCESS_SYSTEM_DPI_AWARE = 1,
			PROCESS_PER_MONITOR_DPI_AWARE = 2
		} PROCESS_DPI_AWARENESS;
		typedef HRESULT(STDAPICALLTYPE* SetProcessDpiAwarenessProc)(PROCESS_DPI_AWARENESS Value);
		const SetProcessDpiAwarenessProc setProcessDpiAwareness = (SetProcessDpiAwarenessProc)GetProcAddress(shCoreDll, "SetProcessDpiAwareness");
		if (setProcessDpiAwareness)
			setProcessDpiAwareness(enable ? PROCESS_PER_MONITOR_DPI_AWARE : PROCESS_DPI_UNAWARE);
		::FreeLibrary(shCoreDll);
	}
    WindowsWindow::WindowsWindow(const std::string& title, const Vector2u& size)
    {
        RECT r;
        r.top = r.left = 100;
        r.right = size.x;
        r.bottom = size.y;
        m_lastSize = size;
		
        DWORD styleEx = WS_EX_APPWINDOW | WS_EX_TOPMOST,  style = WS_OVERLAPPEDWINDOW;
		::AdjustWindowRect(&r, style, false);
        m_hwnd = CreateWindowA(	 
									__TEXT("MeteorEngine"), 
									title.c_str(), 
									style,
									r.left, r.top, 
									r.right, r.bottom,
									NULL, NULL, 
									GetModuleHandle(NULL), 
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

    bool WindowsWindow::PeekEvents(Event& event)
    {
        if(!m_events.empty())
        {
            event = m_events.front();
            m_events.pop();
            return true;
        }
        return false;
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

    KeyCode WindowsWindow::VirtualKeyCodeToIS(WPARAM wParam, LPARAM lParam)
    {
        switch (wParam)
        {
            case VK_SHIFT:
            {
                static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
                UINT scancode = static_cast<UINT>((lParam & (0xFF << 16)) >> 16);
                return scancode == lShift ? KeyCode::LShift : KeyCode::RShift;
            }

            case VK_MENU:		return (HIWORD(lParam) & KF_EXTENDED) ? KeyCode::RAlt : KeyCode::LAlt;
            case VK_CONTROL:	return (HIWORD(lParam) & KF_EXTENDED) ? KeyCode::RControl : KeyCode::LControl;
            case VK_LWIN:       return KeyCode::LSystem;
            case VK_RWIN:       return KeyCode::RSystem;
            case VK_APPS:       return KeyCode::Menu;
            case VK_OEM_1:      return KeyCode::Semicolon;
            case VK_OEM_2:      return KeyCode::Slash;
            case VK_OEM_PLUS:   return KeyCode::Equal;
            case VK_OEM_MINUS:  return KeyCode::Hyphen;
            case VK_OEM_4:      return KeyCode::LBracket;
            case VK_OEM_6:      return KeyCode::RBracket;
            case VK_OEM_COMMA:  return KeyCode::Comma;
            case VK_OEM_PERIOD: return KeyCode::Period;
            case VK_OEM_7:      return KeyCode::Quote;
            case VK_OEM_5:      return KeyCode::Backslash;
            case VK_OEM_3:      return KeyCode::Tilde;
            case VK_ESCAPE:     return KeyCode::Escape;
            case VK_SPACE:      return KeyCode::Space;
            case VK_RETURN:     return KeyCode::Enter;
            case VK_BACK:       return KeyCode::Backspace;
            case VK_TAB:        return KeyCode::Tab;
            case VK_PRIOR:      return KeyCode::PageUp;
            case VK_NEXT:       return KeyCode::PageDown;
            case VK_END:        return KeyCode::End;
            case VK_HOME:       return KeyCode::Home;
            case VK_INSERT:     return KeyCode::Insert;
            case VK_DELETE:     return KeyCode::Delete;
            case VK_ADD:        return KeyCode::Add;
            case VK_SUBTRACT:   return KeyCode::Subtract;
            case VK_MULTIPLY:   return KeyCode::Multiply;
            case VK_DIVIDE:     return KeyCode::Divide;
            case VK_PAUSE:      return KeyCode::Pause;
            case VK_F1:         return KeyCode::F1;
            case VK_F2:         return KeyCode::F2;
            case VK_F3:         return KeyCode::F3;
            case VK_F4:         return KeyCode::F4;
            case VK_F5:         return KeyCode::F5;
            case VK_F6:         return KeyCode::F6;
            case VK_F7:         return KeyCode::F7;
            case VK_F8:         return KeyCode::F8;
            case VK_F9:         return KeyCode::F9;
            case VK_F10:        return KeyCode::F10;
            case VK_F11:        return KeyCode::F11;
            case VK_F12:        return KeyCode::F12;
            case VK_F13:        return KeyCode::F13;
            case VK_F14:        return KeyCode::F14;
            case VK_F15:        return KeyCode::F15;
            case VK_LEFT:       return KeyCode::Left;
            case VK_RIGHT:      return KeyCode::Right;
            case VK_UP:         return KeyCode::Up;
            case VK_DOWN:       return KeyCode::Down;
            case VK_NUMPAD0:    return KeyCode::Numpad0;
            case VK_NUMPAD1:    return KeyCode::Numpad1;
            case VK_NUMPAD2:    return KeyCode::Numpad2;
            case VK_NUMPAD3:    return KeyCode::Numpad3;
            case VK_NUMPAD4:    return KeyCode::Numpad4;
            case VK_NUMPAD5:    return KeyCode::Numpad5;
            case VK_NUMPAD6:    return KeyCode::Numpad6;
            case VK_NUMPAD7:    return KeyCode::Numpad7;
            case VK_NUMPAD8:    return KeyCode::Numpad8;
            case VK_NUMPAD9:    return KeyCode::Numpad9;
            case 'A':           return KeyCode::A;
            case 'Z':           return KeyCode::Z;
            case 'E':           return KeyCode::E;
            case 'R':           return KeyCode::R;
            case 'T':           return KeyCode::T;
            case 'Y':           return KeyCode::Y;
            case 'U':           return KeyCode::U;
            case 'I':           return KeyCode::I;
            case 'O':           return KeyCode::O;
            case 'P':           return KeyCode::P;
            case 'Q':           return KeyCode::Q;
            case 'S':           return KeyCode::S;
            case 'D':           return KeyCode::D;
            case 'F':           return KeyCode::F;
            case 'G':           return KeyCode::G;
            case 'H':           return KeyCode::H;
            case 'J':           return KeyCode::J;
            case 'K':           return KeyCode::K;
            case 'L':           return KeyCode::L;
            case 'M':           return KeyCode::M;
            case 'W':           return KeyCode::W;
            case 'X':           return KeyCode::X;
            case 'C':           return KeyCode::C;
            case 'V':           return KeyCode::V;
            case 'B':           return KeyCode::B;
            case 'N':           return KeyCode::N;
            case '0':           return KeyCode::Num0;
            case '1':           return KeyCode::Num1;
            case '2':           return KeyCode::Num2;
            case '3':           return KeyCode::Num3;
            case '4':           return KeyCode::Num4;
            case '5':           return KeyCode::Num5;
            case '6':           return KeyCode::Num6;
            case '7':           return KeyCode::Num7;
            case '8':           return KeyCode::Num8;
            case '9':           return KeyCode::Num9;
        }
        return KeyCode::None;
    }


    void WindowsWindow::OnEvent(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        bool m_mouseInside = true, m_resizing = false;
        switch (msg)
        {
			case WM_SETCURSOR:
			{
				break;
			}
            case WM_CLOSE:
            {
                Event event;
                event.type        = Event::Closed;
                m_events.push(event);
                break;
            }
            case WM_SIZE:
            {
                if (wParam != SIZE_MINIMIZED && !m_resizing && m_lastSize != GetSize())
                {
                    m_lastSize = GetSize();
                    Event event;
                    event.size.width  = m_lastSize.x;
                    event.size.height = m_lastSize.y;
                    event.type        = Event::Resized;
                    m_events.push(event);
                }
                break;
            }
            /// Start resizing
            case WM_ENTERSIZEMOVE:
            {
                m_resizing = true;
                break;
            }

            /// Stop resizing
            case WM_EXITSIZEMOVE:
            {
                m_resizing = false;
                if(m_lastSize != GetSize())
                {
                    m_lastSize = GetSize();
                    Event event;
                    event.type        = Event::Resized;
                    event.size.width  = m_lastSize.x;
                    event.size.height = m_lastSize.y;
                    m_events.push(event);
                }
                break;
            }
            /// Vertical mouse wheel event
            case WM_MOUSEWHEEL:
            {
                /// Mouse position is in screen coordinates, convert it to window coordinates
                POINT position;
                position.x = static_cast<s16>(LOWORD(lParam));
                position.y = static_cast<s16>(HIWORD(lParam));
                ScreenToClient(m_hwnd, &position);
                s16 delta = static_cast<s16>(HIWORD(wParam));
                Event event;

                event.mouseWheel.delta = delta / 120;
                event.mouseWheel.x     = position.x;
                event.mouseWheel.y     = position.y;
                event.type             = Event::MouseWheelMoved;
                m_events.push(event);


                event.mouseWheelScroll.wheel = MouseWheel::VerticalWheel;
                event.mouseWheelScroll.delta = static_cast<float>(delta) / 120.f;
                event.mouseWheelScroll.x     = position.x;
                event.mouseWheelScroll.y     = position.y;
                event.type                   = Event::MouseWheelScrolled;

                m_events.push(event);
                break;
            }

            /// Horizontal mouse wheel event
            case WM_MOUSEHWHEEL:
            {
                /// Mouse position is in screen coordinates, convert it to window coordinates

                POINT position;
                position.x = static_cast<s16>(LOWORD(lParam));
                position.y = static_cast<s16>(HIWORD(lParam));
                ScreenToClient(m_hwnd, &position);

                s16 delta = static_cast<s16>(HIWORD(wParam));


                Event event;
                event.mouseWheelScroll.wheel = MouseWheel::HorizontalWheel;
                event.mouseWheelScroll.delta = -static_cast<float>(delta) / 120.f;
                event.mouseWheelScroll.x     = position.x;
                event.mouseWheelScroll.y     = position.y;
                event.type                   = Event::MouseWheelScrolled;
                m_events.push(event);
                break;
            }

            /// Mouse left button down event
            case WM_LBUTTONDOWN:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonLeft;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonPressed;
                m_events.push(event);
                break;
            }

            /// Mouse left button up event
            case WM_LBUTTONUP:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonLeft;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonReleased;
                m_events.push(event);
                break;
            }

            /// Mouse right button down event
            case WM_RBUTTONDOWN:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonRight;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonPressed;
                m_events.push(event);
                break;
            }

            /// Mouse right button up event
            case WM_RBUTTONUP:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonRight;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonReleased;
                m_events.push(event);
                break;
            }

            /// Mouse wheel button down event
            case WM_MBUTTONDOWN:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonMiddle;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonPressed;
                m_events.push(event);
                break;
            }

            /// Mouse wheel button up event
            case WM_MBUTTONUP:
            {
                Event event;
                event.mouseButton.button = MouseCode::ButtonMiddle;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonReleased;

                m_events.push(event);
                break;
            }

            /// Mouse X button down event
            case WM_XBUTTONDOWN:
            {
                Event event;
                event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? MouseCode::XButton1 : MouseCode::XButton2;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonPressed;
                m_events.push(event);
                break;
            }

            /// Mouse X button up event
            case WM_XBUTTONUP:
            {
                Event event;

                event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? MouseCode::XButton1 : MouseCode::XButton2;
                event.mouseButton.x      = static_cast<s16>(LOWORD(lParam));
                event.mouseButton.y      = static_cast<s16>(HIWORD(lParam));
                event.type               = Event::MouseButtonReleased;
                m_events.push(event);
                break;
            }

            /// Mouse leave event
            case WM_MOUSELEAVE:
            {
                if (m_mouseInside)
                {
                    m_mouseInside = false;
                    Event event;
                    event.type = Event::MouseLeave;
                    m_events.push(event);
                }
                break;
            }

            /// Mouse move event
            case WM_MOUSEMOVE:
            {
				int x = static_cast<s16>(LOWORD(lParam));
				int y = static_cast<s16>(HIWORD(lParam));
                /// Extract the mouse local coordinates
                /**


                /// Get the client area of the window
                RECT area;
                GetClientRect(m_hwnd, &area);

                /// Capture the mouse in case the user wants to drag it outside
                if ((wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0)
                {
                    /// Only release the capture if we really have it
                    if (GetCapture() == m_hwnd)
                        ReleaseCapture();
                }
                else if (GetCapture() != m_hwnd)
                {
                    /// Set the capture to continue receiving mouse events
                    SetCapture(m_hwnd);
                }

                /// If the cursor is outside the client area...
                if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom))
                {
                    /// and it used to be inside, the mouse left it.
                    if (m_mouseInside)
                    {
                        m_mouseInside = false;

                        /// No longer care for the mouse leaving the window
                        setTracking(false);

                        /// Generate a MouseLeft event
                        Event event;
                        event.type = Event::MouseLeft;
                        pushEvent(event);
                    }
                }
                else
                {
                    /// and vice-versa
                    if (!m_mouseInside)
                    {
                        m_mouseInside = true;

                        /// Look for the mouse leaving the window
                        setTracking(true);

                        /// Generate a MouseEntered event
                        Event event;
                        event.type = Event::MouseEntered;
                        pushEvent(event);
                    }
                }*/

                /// Generate a MouseMove event
                Event event;
                event.mouseMove.x = x;
                event.mouseMove.y = y;
                event.type        = Event::MouseMoved;
                m_events.push(event);
                break;
            }
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            {
                if (((HIWORD(lParam) & KF_REPEAT) == 0))
                {
                    Event event;
                    event.type                = Event::KeyPressed;
                    event.keyEvent.alt        = HIWORD(GetKeyState(VK_MENU))    != 0;
                    event.keyEvent.control    = HIWORD(GetKeyState(VK_CONTROL)) != 0;
                    event.keyEvent.shift      = HIWORD(GetKeyState(VK_SHIFT))   != 0;
                    event.keyEvent.system     = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
                    event.keyEvent.code       = VirtualKeyCodeToIS(wParam, lParam);
                    m_events.push(event);
                }
                break;
            }

            case WM_KEYUP:
            case WM_SYSKEYUP:
            {
                Event event;
                event.type                = Event::KeyReleased;
                event.keyEvent.alt        = HIWORD(GetKeyState(VK_MENU))    != 0;
                event.keyEvent.control    = HIWORD(GetKeyState(VK_CONTROL)) != 0;
                event.keyEvent.shift      = HIWORD(GetKeyState(VK_SHIFT))   != 0;
                event.keyEvent.system     = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
                event.keyEvent.code       = VirtualKeyCodeToIS(wParam, lParam);
                m_events.push(event);
                break;
            }
			case WM_DPICHANGED:
				if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
				{
					const RECT* suggested_rect = (RECT*)lParam;
					::SetWindowPos(m_hwnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
				}
        }

    }

}
