#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H

#include "../../Core/Config.h"
#include "../VertexBuffer.h"
namespace MeteorEngine
{
    class METEOR_API OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float *vertices, u32 size);
        virtual ~OpenGLVertexBuffer();
        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual void SetBufferLayout(const BufferLayout& layouts) override;
        virtual const BufferLayout& GetBufferLayout() const override;
    private:
        u32 m_buffer;
        BufferLayout m_bufferLayout;
    };
}
#endif // OPENGLVERTEXBUFFER_H
