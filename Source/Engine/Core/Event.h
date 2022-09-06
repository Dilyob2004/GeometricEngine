#ifndef EVENT_H
#define EVENT_H
#include <Engine/Core/Config.h>
#include <Engine/Core/MouseCodes.h>
#include <Engine/Core/KeyCodes.h>
namespace MeteorEngine
{
    class Event
    {
    public:
        struct SizeEvent { u32 width, height; };
        struct KeyEvent { KeyCode code; bool alt, control, shift, system; };
        struct MouseButtonEvent { MouseCode button; s32 x, y; };
        struct MouseMoveEvent { s32 x, y; };
        struct MouseWheelEvent { s32 delta, x, y; };
        struct MouseWheelScrollEvent { MouseWheel wheel; f32 delta; s32 x, y; };

        enum EnumEventType
        {
            Closed, Resized, KeyPressed, KeyReleased, MouseWheelMoved, MouseWheelScrolled,
            MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseEntered, MouseLeft, MouseLeave
        };






        SizeEvent             size;
        MouseMoveEvent        mouseMove;
        MouseButtonEvent      mouseButton;
        MouseWheelEvent       mouseWheel;
        MouseWheelScrollEvent mouseWheelScroll;
        KeyEvent keyEvent;
        EnumEventType   type;
    };
}

#endif // EVENT_H
