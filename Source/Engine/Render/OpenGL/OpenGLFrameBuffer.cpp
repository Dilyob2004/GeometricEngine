#include <Engine/Render/OpenGL/OpenGLFrameBuffer.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
namespace MeteorEngine
{

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec& spec):
        m_specification(spec)
    {
        Invalidate();
    }
    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
    }
    void OpenGLFrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
        glViewport(0, 0, m_specification.Size.x, m_specification.Size.y);
    }
    void OpenGLFrameBuffer::UnBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
	GLenum countAttachment = 0;
	GLenum GetAttachments(const RHITextureFormat& format)
	{
		if (Texture::IsDepthStencilFormat(format))
			return	GL_DEPTH_STENCIL_ATTACHMENT;

		if (Texture::IsStencilFormat(format))
			return	GL_STENCIL_ATTACHMENT;

		if (Texture::IsDepthFormat(format))
			return	GL_DEPTH_ATTACHMENT;

		GLenum value = GL_COLOR_ATTACHMENT0 + countAttachment;
		countAttachment++;
		return value;
	}
	void OpenGLFrameBuffer::AddTextureAttachment(Texture2D* texture)
	{
		GLenum attachment = GetAttachments(texture->GetFormat());
		if (attachment != GL_DEPTH_STENCIL_ATTACHMENT ||
			attachment != GL_DEPTH_ATTACHMENT ||
			attachment != GL_STENCIL_ATTACHMENT)
			m_AttachmentData.emplace_back(attachment);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetTexture(), 0);


	}
    void OpenGLFrameBuffer::Invalidate()
    {
        if(m_frameBuffer)
        {
            glDeleteFramebuffers(1, &m_frameBuffer);
        }
        glCreateFramebuffers(1, &m_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

		AddTextureAttachment(Texture2D::Create(RHITextureFormat::RGB8_UNORM, m_specification.Size.x, m_specification.Size.y));
		if(m_AttachmentData.size())
			glDrawBuffers(m_AttachmentData.size(), m_AttachmentData.data());
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void OpenGLFrameBuffer::Resize(const Vector2u &size)
    {
        m_specification.Size = size;
        Invalidate();
    }
}
