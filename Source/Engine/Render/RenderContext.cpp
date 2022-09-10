#include <Engine/Render/RenderContext.h>
#include <Engine/Platform/Win32/WindowsOpenGL.h>
namespace MeteorEngine
{
	RenderContext* RenderContext::Create(const Window* window)
    {
         return new WindowsOpenGL((HWND)window->GetWindowPtr());
    }
}
