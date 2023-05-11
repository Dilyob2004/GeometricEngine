#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H
#include <Engine/Core/Config.h>
#include <Engine/InputDevice/KeyCodes.h>
#include <Engine/InputDevice/MouseCodes.h>
#include <Engine/Math/Vector2.h>
namespace GeometricEngine
{
    class GEOMETRIC_API WindowsInput
    {
    public:

		static void Initialize();
		static void Tick();

		static bool GetKey(KeyCode Key);
		static bool GetKeyDown(KeyCode Key);
		static bool GetKeyUp(KeyCode Key);


		static bool GetMouseButton(MouseCode Key);
		static bool GetMouseButtonDown(MouseCode Key);
		static bool GetMouseButtonUp(MouseCode Key);

		static Vector2f GetMousePosition();
		static Vector2f GetMousePositionDelta();
		static F32		GetMouseWhellDelta();

		static bool OnResized(U32&, U32&);
		static bool OnResized();
		static bool OnClosed();

		static void Reset();
		static void WndProc(HWND, UINT, WPARAM, LPARAM);
    };
}

#endif // WINDOWSINPUT_H
