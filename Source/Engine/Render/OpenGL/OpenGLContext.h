#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include "../../Core/Window.h"
namespace MeteorEngine
{
    class METEOR_API OpenGLContext
    {
    public:
        virtual ~OpenGLContext(){}
        virtual void SetVSync(bool) = 0;
        static OpenGLContext *Create(const Window *);
        virtual void MakeCurrent(bool) = 0;
        virtual void *GetCurrent() = 0;
        virtual void Renderer() = 0;
    };
}
#endif // OPENGLCONTEXT_H
