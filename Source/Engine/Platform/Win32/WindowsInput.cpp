#include <Engine/Platform/Win32/WindowsInput.h>
#include <windows.h>
#include <memory>
namespace MeteorEngine
{
    Vector2f WindowsInput::GetMousePosition()
    {
        POINT point;
        GetCursorPos(&point);
        return Vector2f((f32)point.x, (f32)point.y);
    }
    Vector2f WindowsInput::GetMousePosition(HWND hwnd)
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(hwnd, &point);
        return Vector2f((f32)point.x, (f32)point.y);
    }
    void WindowsInput::SetMousePosition(const Vector2i& position)
    {
        SetCursorPos(position.x, position.y);
    }
    void WindowsInput::SetMousePosition(const Vector2i& position, HWND hwnd)
    {
        POINT point = {position.x, position.y};
        ClientToScreen(hwnd, &point);
        SetCursorPos(point.x, point.y);
    }

    bool WindowsInput::GetMouseButtonDown(MouseCode button)
    {
        int vkey = -1;
        switch (button)
        {
            case MouseCode::ButtonLeft:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON;   break;
            case MouseCode::ButtonRight:    vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON;   break;
            case MouseCode::ButtonMiddle:   vkey = VK_MBUTTON;                                                  break;
            case MouseCode::XButton1:       vkey = VK_XBUTTON1;                                                 break;
            case MouseCode::XButton2:       vkey = VK_XBUTTON2;                                                 break;
            default:                        vkey = -1;                                                          break;
        }
        return (GetAsyncKeyState(vkey) & 0x8000) != 0;
    }
    bool WindowsInput::GetKeyDown(KeyCode key)
    {
            int vkey = 0;
            switch (key)
            {
                default:                  vkey = 0;             break;
                case KeyCode::A:          vkey = 'A';           break;
                case KeyCode::B:          vkey = 'B';           break;
                case KeyCode::C:          vkey = 'C';           break;
                case KeyCode::D:          vkey = 'D';           break;
                case KeyCode::E:          vkey = 'E';           break;
                case KeyCode::F:          vkey = 'F';           break;
                case KeyCode::G:          vkey = 'G';           break;
                case KeyCode::H:          vkey = 'H';           break;
                case KeyCode::I:          vkey = 'I';           break;
                case KeyCode::J:          vkey = 'J';           break;
                case KeyCode::K:          vkey = 'K';           break;
                case KeyCode::L:          vkey = 'L';           break;
                case KeyCode::M:          vkey = 'M';           break;
                case KeyCode::N:          vkey = 'N';           break;
                case KeyCode::O:          vkey = 'O';           break;
                case KeyCode::P:          vkey = 'P';           break;
                case KeyCode::Q:          vkey = 'Q';           break;
                case KeyCode::R:          vkey = 'R';           break;
                case KeyCode::S:          vkey = 'S';           break;
                case KeyCode::T:          vkey = 'T';           break;
                case KeyCode::U:          vkey = 'U';           break;
                case KeyCode::V:          vkey = 'V';           break;
                case KeyCode::W:          vkey = 'W';           break;
                case KeyCode::X:          vkey = 'X';           break;
                case KeyCode::Y:          vkey = 'Y';           break;
                case KeyCode::Z:          vkey = 'Z';           break;
                case KeyCode::Num0:       vkey = '0';           break;
                case KeyCode::Num1:       vkey = '1';           break;
                case KeyCode::Num2:       vkey = '2';           break;
                case KeyCode::Num3:       vkey = '3';           break;
                case KeyCode::Num4:       vkey = '4';           break;
                case KeyCode::Num5:       vkey = '5';           break;
                case KeyCode::Num6:       vkey = '6';           break;
                case KeyCode::Num7:       vkey = '7';           break;
                case KeyCode::Num8:       vkey = '8';           break;
                case KeyCode::Num9:       vkey = '9';           break;
                case KeyCode::Escape:     vkey = VK_ESCAPE;     break;
                case KeyCode::LControl:   vkey = VK_LCONTROL;   break;
                case KeyCode::LShift:     vkey = VK_LSHIFT;     break;
                case KeyCode::LAlt:       vkey = VK_LMENU;      break;
                case KeyCode::LSystem:    vkey = VK_LWIN;       break;
                case KeyCode::RControl:   vkey = VK_RCONTROL;   break;
                case KeyCode::RShift:     vkey = VK_RSHIFT;     break;
                case KeyCode::RAlt:       vkey = VK_RMENU;      break;
                case KeyCode::RSystem:    vkey = VK_RWIN;       break;
                case KeyCode::Menu:       vkey = VK_APPS;       break;
                case KeyCode::LBracket:   vkey = VK_OEM_4;      break;
                case KeyCode::RBracket:   vkey = VK_OEM_6;      break;
                case KeyCode::Semicolon:  vkey = VK_OEM_1;      break;
                case KeyCode::Comma:      vkey = VK_OEM_COMMA;  break;
                case KeyCode::Period:     vkey = VK_OEM_PERIOD; break;
                case KeyCode::Quote:      vkey = VK_OEM_7;      break;
                case KeyCode::Slash:      vkey = VK_OEM_2;      break;
                case KeyCode::Backslash:  vkey = VK_OEM_5;      break;
                case KeyCode::Tilde:      vkey = VK_OEM_3;      break;
                case KeyCode::Equal:      vkey = VK_OEM_PLUS;   break;
                case KeyCode::Hyphen:     vkey = VK_OEM_MINUS;  break;
                case KeyCode::Space:      vkey = VK_SPACE;      break;
                case KeyCode::Enter:      vkey = VK_RETURN;     break;
                case KeyCode::Backspace:  vkey = VK_BACK;       break;
                case KeyCode::Tab:        vkey = VK_TAB;        break;
                case KeyCode::PageUp:     vkey = VK_PRIOR;      break;
                case KeyCode::PageDown:   vkey = VK_NEXT;       break;
                case KeyCode::End:        vkey = VK_END;        break;
                case KeyCode::Home:       vkey = VK_HOME;       break;
                case KeyCode::Insert:     vkey = VK_INSERT;     break;
                case KeyCode::Delete:     vkey = VK_DELETE;     break;
                case KeyCode::Add:        vkey = VK_ADD;        break;
                case KeyCode::Subtract:   vkey = VK_SUBTRACT;   break;
                case KeyCode::Multiply:   vkey = VK_MULTIPLY;   break;
                case KeyCode::Divide:     vkey = VK_DIVIDE;     break;
                case KeyCode::Left:       vkey = VK_LEFT;       break;
                case KeyCode::Right:      vkey = VK_RIGHT;      break;
                case KeyCode::Up:         vkey = VK_UP;         break;
                case KeyCode::Down:       vkey = VK_DOWN;       break;
                case KeyCode::Numpad0:    vkey = VK_NUMPAD0;    break;
                case KeyCode::Numpad1:    vkey = VK_NUMPAD1;    break;
                case KeyCode::Numpad2:    vkey = VK_NUMPAD2;    break;
                case KeyCode::Numpad3:    vkey = VK_NUMPAD3;    break;
                case KeyCode::Numpad4:    vkey = VK_NUMPAD4;    break;
                case KeyCode::Numpad5:    vkey = VK_NUMPAD5;    break;
                case KeyCode::Numpad6:    vkey = VK_NUMPAD6;    break;
                case KeyCode::Numpad7:    vkey = VK_NUMPAD7;    break;
                case KeyCode::Numpad8:    vkey = VK_NUMPAD8;    break;
                case KeyCode::Numpad9:    vkey = VK_NUMPAD9;    break;
                case KeyCode::F1:         vkey = VK_F1;         break;
                case KeyCode::F2:         vkey = VK_F2;         break;
                case KeyCode::F3:         vkey = VK_F3;         break;
                case KeyCode::F4:         vkey = VK_F4;         break;
                case KeyCode::F5:         vkey = VK_F5;         break;
                case KeyCode::F6:         vkey = VK_F6;         break;
                case KeyCode::F7:         vkey = VK_F7;         break;
                case KeyCode::F8:         vkey = VK_F8;         break;
                case KeyCode::F9:         vkey = VK_F9;         break;
                case KeyCode::F10:        vkey = VK_F10;        break;
                case KeyCode::F11:        vkey = VK_F11;        break;
                case KeyCode::F12:        vkey = VK_F12;        break;
                case KeyCode::F13:        vkey = VK_F13;        break;
                case KeyCode::F14:        vkey = VK_F14;        break;
                case KeyCode::F15:        vkey = VK_F15;        break;
                case KeyCode::Pause:      vkey = VK_PAUSE;      break;
            }
            return (GetAsyncKeyState(vkey) & 0x8000) != 0;
    }
}
