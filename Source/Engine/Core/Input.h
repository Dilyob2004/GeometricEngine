#ifndef INPUT_H
#define INPUT_H
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/MouseCodes.h>
#include <Engine/Core/KeyCodes.h>
namespace MeteorEngine
{
    class METEOR_API Input
    {
        public:
            static Vector2f GetMousePosition ();
            static Vector2f GetMousePosition (const Window&);

            static void SetMousePosition (const Vector2i&);
            static void SetMousePosition (const Vector2i&, const Window&);

            static bool     GetMouseButtonDown (MouseCode);
            static bool     GetKeyDown         (KeyCode);
    };
}

#endif // INPUT_H
