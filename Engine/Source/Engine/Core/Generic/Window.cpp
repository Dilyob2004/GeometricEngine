


#include <Engine/Core/Generic/Window.h>
#include <Engine/Core/Windows/WindowsWindow.h>
Window * Window::Create(const WindowDefinition& Definition)
{
    return new WindowsWindow(Definition);
}
