#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H
#include <Engine/Core/MouseCodes.h>
#include <Engine/Core/KeyCodes.h>
#include <Engine/Math/Vector2.h>

#include <windows.h>
namespace MeteorEngine
{
    class METEOR_API WindowsInput
    {
        public:
            static Vector2f GetMousePosition ();
            static Vector2f GetMousePosition (HWND);

            static void SetMousePosition (const Vector2i&);
            static void SetMousePosition (const Vector2i&, HWND);

            static bool     GetMouseButtonDown (MouseCode);
            static bool     GetKeyDown         (KeyCode);
    };
}

#endif // WINDOWSINPUT_H
