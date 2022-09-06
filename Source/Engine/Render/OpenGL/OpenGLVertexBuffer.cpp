#include <Engine/Render/OpenGL/OpenGLVertexBuffer.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
namespace MeteorEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(f32 *vertices, u32 size)
    {
        glCreateBuffers(1, &m_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        if(m_buffer)
            glDeleteBuffers(1, &m_buffer);
    }
    void OpenGLVertexBuffer::SetBufferLayout(const BufferLayout& layout)
    {
        m_bufferLayout = layout;
    }

    const BufferLayout& OpenGLVertexBuffer::GetBufferLayout() const
    {
        return m_bufferLayout;
    }
    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    }
    void OpenGLVertexBuffer::UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
