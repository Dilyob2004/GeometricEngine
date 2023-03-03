#include <Engine/Core/Windows/WindowsInput.h>
#include <Engine/InputDevice/Keyboard.h>
#include <Engine/InputDevice/Mouse.h>
#include <Engine/InputCore/InputCore.h>
namespace GeometricEngine
{
	KeyCode WindowsKeyToKeyCode(WPARAM WParam, LPARAM Flags)
	{
		switch (WParam)
		{
			case VK_SHIFT:
			{
				static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
				UINT Scancode = static_cast<UINT>((Flags & (0xFF << 16)) >> 16);
				return Scancode == lShift ? KeyCode::LShift : KeyCode::RShift;
			}
			case VK_MENU: return (HIWORD(Flags) & KF_EXTENDED) ? KeyCode::RAlt : KeyCode::LAlt;
			case VK_CONTROL: return (HIWORD(Flags) & KF_EXTENDED) ? KeyCode::RControl : KeyCode::LControl;


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
	class WindowsKeyboard : public Keyboard
	{
	public:
		explicit WindowsKeyboard()
			: Keyboard()
		{
		}
		void WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
		{
			switch (Msg)
			{
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				{
					OnKey(EventType::KeyDown, WindowsKeyToKeyCode(WParam, LParam));
					break;
				}

				case WM_KEYUP:
				case WM_SYSKEYUP:
				{
					OnKey(EventType::KeyUp, WindowsKeyToKeyCode(WParam, LParam));
					break;
				}
			}
		}
	};
	class WindowsMouse : public Mouse
	{
	public:
		explicit WindowsMouse()
			: Mouse()
		{
		}
		void WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
		{
			POINT Point;
			Point.x = static_cast<LONG>((int)(short)LOWORD(LParam));
			Point.y = static_cast<LONG>((int)(short)HIWORD(LParam));
			ClientToScreen(hWnd, &Point);
			const Vector2f Position(static_cast<F32>(Point.x), static_cast<F32>(Point.y));
			switch (Msg)
			{

				case WM_LBUTTONDOWN:
					OnMouse(EventType::MouseDown, MouseCode::ButtonLeft);
					break;
				case WM_RBUTTONDOWN:
					OnMouse(EventType::MouseDown, MouseCode::ButtonRight);
					break;
				case WM_MBUTTONDOWN:
					OnMouse(EventType::MouseDown, MouseCode::ButtonMiddle);
					break;				
				
				case WM_LBUTTONDBLCLK:
					OnMouse(EventType::MouseDoubleClick, MouseCode::ButtonLeft);
					break;
				case WM_RBUTTONDBLCLK:
					OnMouse(EventType::MouseDoubleClick, MouseCode::ButtonRight);
					break;
				case WM_MBUTTONDBLCLK:
					OnMouse(EventType::MouseDoubleClick, MouseCode::ButtonMiddle);
					break;


				case WM_LBUTTONUP:
					OnMouse(EventType::MouseUp, MouseCode::ButtonLeft);
					break;
				case WM_RBUTTONUP:
					OnMouse(EventType::MouseUp, MouseCode::ButtonRight);
					break;
				case WM_MBUTTONUP:
					OnMouse(EventType::MouseUp, MouseCode::ButtonMiddle);
					break;


				case WM_MOUSEWHEEL: 
				{
					const short Delta = (short)HIWORD(WParam);
					if (Delta != 0)
						OnMouseWheel(static_cast<F32>(Delta) / 120.f);
					break;
				}

				case WM_MOUSEMOVE:
					OnMouseMove(Position);
					break;
			
			}
		}
	};


	static WindowsKeyboard*		GPlatformKeyboard = NULL;
	static WindowsMouse*		GPlatformMouse = NULL;


	static bool Initialized = false;
	bool WindowsInput::Initialize()
	{
		GPlatformKeyboard	= new WindowsKeyboard();
		GPlatformMouse		= new WindowsMouse();

		if (!GPlatformKeyboard)
			return false;		
		
		if (!GPlatformMouse)
			return false;



		Initialized = true;
		return true;
	}	
	bool WindowsInput::HasInitialized()
	{
		return Initialized;
	}

	bool WindowsInput::GetKey(KeyCode Key)
	{
		return GPlatformKeyboard->GetKey(Key);
	}
	bool WindowsInput::GetKeyDown(KeyCode Key)
	{
		return GPlatformKeyboard->GetKeyDown(Key);
	}
	bool WindowsInput::GetKeyUp(KeyCode Key)
	{
		return GPlatformKeyboard->GetKeyUp(Key);
	}

	bool WindowsInput::GetMouseButton(MouseCode Code)
	{
		return GPlatformMouse->GetButton(Code);
	}
	bool WindowsInput::GetMouseButtonDown(MouseCode Code)
	{
		return GPlatformMouse->GetButtonDown(Code);
	}
	bool WindowsInput::GetMouseButtonUp(MouseCode Code)
	{
		return GPlatformMouse->GetButtonUp(Code);
	}

	void WindowsInput::DeInitialize()
	{
	}
	void WindowsInput::Tick()
	{
		GPlatformKeyboard->Tick();
		GPlatformMouse->Tick();
	}	
	void WindowsInput::Reset()
	{
		GPlatformKeyboard->Reset();
		GPlatformMouse->Reset();
	}
	void WindowsInput::WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
	{
		GPlatformKeyboard->WndProc(hWnd, Msg, WParam, LParam);
		GPlatformMouse->WndProc(hWnd, Msg, WParam, LParam);
	}
}
