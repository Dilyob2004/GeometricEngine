#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include <Engine/Core/Window.h>



namespace MeteorEngine
{
    class METEOR_API RenderContext
    {
    public:
        virtual ~RenderContext(){}
        static RenderContext* Create(Window *);

		//virtual Window* GetWindow() const = 0;
    };
}
#endif // OPENGLCONTEXT_H
