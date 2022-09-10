#include <Engine/Core/Input.h>
#include <Engine/Platform/Win32/WindowsInput.h>

namespace MeteorEngine
{

    Vector2f Input::GetMousePosition()
    {
        return WindowsInput::GetMousePosition();
    }
    Vector2f Input::GetMousePosition(const Window& window)
    {
        return WindowsInput::GetMousePosition(reinterpret_cast<HWND>(window.GetWindowPtr()));
    }

    void Input::SetMousePosition (const Vector2i& position)
    {
        WindowsInput::SetMousePosition(position);
    }
    void Input::SetMousePosition (const Vector2i& position, const Window& window)
    {
        WindowsInput::SetMousePosition(position, reinterpret_cast<HWND>(window.GetWindowPtr()));
    }
    bool Input::GetMouseButtonDown (MouseCode code)
    {
        return WindowsInput::GetMouseButtonDown(code);
    }
    bool Input::GetKeyDown (KeyCode code)
    {
        return WindowsInput::GetKeyDown(code);
    }
}
