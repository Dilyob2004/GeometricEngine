#include "OpenGLTexture.h"


#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION


#include <stb_image/stb_image.h>
#ifdef STB_IMAGE_IMPLEMENTATION
#undef STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION
#include <Engine/Platform/Win32/OpenGLSupport.h>

#include <iostream>
#include <vector>
namespace MeteorEngine
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        s32 width = 0, height = 0, channels = 0;


        stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        GLenum internalFormat, dataFormat;
        if(channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;

        }
        glCreateTextures    (GL_TEXTURE_2D, 1, &m_texture);
        glTextureStorage2D  (m_texture, 1, internalFormat, width, height);

        glTexParameteri     (m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri     (m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
        glTexParameteri     (m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri     (m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTextureSubImage2D(m_texture, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
		    
        m_size.x = width;
        m_size.y = height;
        stbi_image_free(data);

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
    void OpenGLTexture2D::UnBind()   const
    {

    }
}
