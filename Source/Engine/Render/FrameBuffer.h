#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
    struct FrameBufferSpecification
    {
        Vector2u size;
        u32 samples = 2;
        bool swapChainTarget = false;
    };
    class METEOR_API FrameBuffer
    {
    public:
        virtual ~FrameBuffer() {}
        virtual void Bind()     const = 0;
        virtual void UnBind()   const = 0;
        virtual void Resize(const Vector2u &) = 0;
        virtual u32 GetColorAttachmentFrameBuffer() const  = 0;
        virtual const FrameBufferSpecification& GetSpecification() const = 0;
        static FrameBuffer* Create(const FrameBufferSpecification&);
    };
}
#endif // FRAMEBUFFER_H
