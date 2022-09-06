#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H
#include "../FrameBuffer.h"
namespace MeteorEngine
{
    class METEOR_API OpenGLFrameBuffer: public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();
        virtual u32 GetColorAttachmentFrameBuffer() const override{ return m_colorAttachment; }
        virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }
        virtual void Bind()     const override;
        virtual void UnBind()   const override;
        virtual void Resize(const Vector2u &) override;
    private:
        void Invalidate();
        FrameBufferSpecification m_specification;
        u32 m_frameBuffer = 0, m_colorAttachment = 0, m_depthAttachment = 0;
    };
}
#endif // OPENGLFRAMEBUFFER_
