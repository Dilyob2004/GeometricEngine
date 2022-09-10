#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include <Engine/Core/Window.h>



namespace MeteorEngine
{
    class METEOR_API RenderContext
    {
    public:
        virtual ~RenderContext(){}
        virtual void SetVSync(bool) = 0;
        static RenderContext*Create(const Window *);
        virtual void MakeCurrent(bool) = 0;
        virtual void *GetCurrent() = 0;
        virtual void Renderer() = 0;
    };
}
#endif // OPENGLCONTEXT_H
