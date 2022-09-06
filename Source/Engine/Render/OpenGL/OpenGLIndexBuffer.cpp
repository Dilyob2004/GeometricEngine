#include <Engine/Render/OpenGL/OpenGLIndexBuffer.h>

#include <Engine/Platform/Win32/OpenGLSupport.h>


namespace MeteorEngine
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(u32 *indices, u32 count):
        m_count(count)
    {
        glCreateBuffers(1, &m_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        if(m_buffer)
            glDeleteBuffers(1, &m_buffer);
    }
    u32 OpenGLIndexBuffer::GetCount() const
    {
        return m_count;
    }
    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
    }
    void OpenGLIndexBuffer::UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
