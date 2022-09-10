#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H
#include <Engine/Render/VertexBuffer.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(f32 *vertices, u32 size);
        virtual ~OpenGLVertexBuffer();
        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual void SetBufferLayout(const BufferLayout& layouts) override { m_bufferLayout = layouts; }
        virtual const BufferLayout& GetBufferLayout() const override { return m_bufferLayout; }
    private:
		u32 m_buffer { 0 };
		BufferLayout m_bufferLayout { };
    };
}
#endif // OPENGLVERTEXBUFFER_H
