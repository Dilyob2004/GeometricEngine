#include <Engine/Render/OpenGL/OpenGLFrameBuffer.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
namespace MeteorEngine
{

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec):
        m_specification(spec)
    {
        Invalidate();
    }
    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
        glDeleteTextures(1, &m_colorAttachment);
        //glDeleteTextures(1, &m_depthAttachment);
    }
    void OpenGLFrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
        glViewport(0, 0, m_specification.size.x, m_specification.size.y);
    }
    void OpenGLFrameBuffer::UnBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void OpenGLFrameBuffer::Invalidate()
    {
        if(m_frameBuffer && m_colorAttachment)
        {
            glDeleteFramebuffers(1, &m_frameBuffer);
            glDeleteTextures(1, &m_colorAttachment);
            //glDeleteTextures(1, &m_depthAttachment);

        }
        glCreateFramebuffers(1, &m_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

        glCreateTextures (GL_TEXTURE_2D, 1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.size.x, m_specification.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);


		//const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, buffers);

		/**glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		//glTextureStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.size.x, m_specification.size.y);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.size.x, m_specification.size.y,
			0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
			*/

		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);



        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void OpenGLFrameBuffer::Resize(const Vector2u &size)
    {
        m_specification.size = size;
        Invalidate();
    }
}
