


#include <Engine/Core/Generic/Window.h>
#include <Engine/Core/Windows/WindowsWindow.h>
namespace GeometricEngine
{
    Window * Window::Create(const std::string& title, const Vector2u& size)
    {
        return new WindowsWindow(title, size);
    }
}
