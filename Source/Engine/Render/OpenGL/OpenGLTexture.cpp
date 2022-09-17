#include <Engine/Platform/Win32/OpenGLSupport.h>
#include <Engine/Render/OpenGL/OpenGLTexture.h>
#include <Engine/Render/ImageCore.h>
namespace MeteorEngine
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path):
		m_texture(0),
		m_size(0, 0)
    {
		ImageCore imageCore;
		if (imageCore.Load(path))
		{
			GLenum internalFormat, dataFormat;
			if (imageCore.GetChannels() == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;

			}
			glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
			glTextureStorage2D(m_texture, 1, internalFormat, imageCore.GetSize().x, imageCore.GetSize().y);

			glTexParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP);

			glTexParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			glTextureSubImage2D(m_texture, 0, 0, 0, imageCore.GetSize().x, imageCore.GetSize().y, dataFormat, GL_UNSIGNED_BYTE, imageCore.GetPointer());

			m_size.x = imageCore.GetSize().x;
			m_size.y = imageCore.GetSize().y;

		}



    }
    OpenGLTexture2D::~OpenGLTexture2D()
    {
        if(m_texture)
            glDeleteTextures(1, &m_texture);
    }
    void OpenGLTexture2D::Bind(u32 slot) const
    {
        glBindTextureUnit(slot, m_texture);
    }
    u32 OpenGLTexture2D::GetTexture() const
    {
        return m_texture;
    }
    void OpenGLTexture2D::UnBind(u32 slot)   const
    {
		glBindTextureUnit(slot, 0);
    }
}
