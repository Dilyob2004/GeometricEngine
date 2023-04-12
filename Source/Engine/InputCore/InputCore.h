#ifndef INPUTCORE_H
#define INPUTCORE_H
#include <Engine/Math/Vector2.h>
#include <Engine/InputDevice/KeyCodes.h>
#include <Engine/InputDevice/MouseCodes.h>
namespace GeometricEngine
{
    class GEOMETRIC_API Input
    {
    public:

		static bool GetKey(KeyCode Key);
		static bool GetKeyDown(KeyCode Key);
		static bool GetKeyUp(KeyCode Key);

		static bool GetMouseButton(MouseCode Key);
		static bool GetMouseButtonDown(MouseCode Key);
		static bool GetMouseButtonUp(MouseCode Key);

		static Vector2f GetMousePosition();
		static Vector2f GetMousePositionDelta();
		static F32		GetMouseWhellDelta();


		static bool OnWindowResized(U32&, U32&);
		static bool OnWindowResized();
		static bool OnWindowClosed();
    };
}

#endif // INPUTCORE_H
