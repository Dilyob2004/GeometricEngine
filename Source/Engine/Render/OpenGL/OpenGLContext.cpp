#include <Engine/Render/OpenGL/OpenGLContext.h>
#include <Engine/Platform/Win32/WindowsOpenGL.h>
namespace MeteorEngine
{
    OpenGLContext* OpenGLContext::Create(const Window* window)
    {
         return new WindowsOpenGL((HWND)window->GetWindowPtr());
    }
}
