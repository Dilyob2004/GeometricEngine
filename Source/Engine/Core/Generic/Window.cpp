


#include <Engine/Core/Generic/Window.h>
#include <Engine/Core/Windows/WindowsWindow.h>
namespace GeometricEngine
{
    Window * Window::Create(const WindowInfoDefinition& Definition)
    {
        return new WindowsWindow(Definition);
    }
}
