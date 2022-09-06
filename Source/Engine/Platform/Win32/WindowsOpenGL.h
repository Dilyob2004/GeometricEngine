#ifndef WINDOWSOPENGL_H
#define WINDOWSOPENGL_H
#include <windows.h>

#include <Engine/Core/Config.h>
#include <Engine/Render/OpenGL/OpenGLContext.h>

namespace MeteorEngine
{
    class METEOR_API WindowsOpenGL : public OpenGLContext
    {
    public:
        WindowsOpenGL(HWND);
        virtual ~WindowsOpenGL();
        virtual void SetVSync(bool);

        virtual void* GetCurrent();
        virtual void MakeCurrent(bool);

        virtual void Renderer();
    private:
        HDC             m_hdc;
        HGLRC           m_hrc;
        HWND            m_wnd;
    };
}
#endif // WINDOWSOPENGL_H
