


#include <Engine/Core/Window.h>
#include <Engine/Platform/Win32/WindowsWindow.h>
namespace MeteorEngine
{
    Window * Window::Create(const std::string& title, const Vector2u& size)
    {
        return new WindowsWindow(title, size);
    }
}
