#include <Engine/Platform/Win32/OpenGLSupport.h>
#include <Engine/Render/OpenGL/OpenGLTexture.h>
#include <Engine/Render/ImageCore.h>
namespace MeteorEngine
{
	u32 MeteorTextureFormatToOpenGLTextureFormat(RHITextureFormat format, bool srgb)
	{
		switch (format)
		{
		case RHITextureFormat::R8_UNORM:					return GL_R8;
		case RHITextureFormat::RG8_UNORM:					return GL_RG8;
		case RHITextureFormat::RGB8_UNORM:					return srgb ? GL_SRGB8 : GL_RGB8;
		case RHITextureFormat::RGBA8_UNORM:					return srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8;

		case RHITextureFormat::RG11B10_F32:					return GL_R11F_G11F_B10F;
		case RHITextureFormat::RGB10A2_UNORM:				return GL_RGB10_A2;

		case RHITextureFormat::R16_F32:						return GL_R16F;
		case RHITextureFormat::RG16_F32:					return GL_RG16F;
		case RHITextureFormat::RGB16_F32:					return GL_RGB16F;
		case RHITextureFormat::RGBA16_F32:					return GL_RGBA16F;

		case RHITextureFormat::R32_F32:						return GL_R32F;
		case RHITextureFormat::RG32_F32:					return GL_RG32F;
		case RHITextureFormat::RGB32_F32:					return GL_RGB32F;
		case RHITextureFormat::RGBA32_F32:					return GL_RGBA32F;

		case RHITextureFormat::DEPTH24_UNORM_STENCIL8_U32:	return GL_DEPTH24_STENCIL8;
		case RHITextureFormat::DEPTH32_F32_STENCIL8_U32:	return GL_DEPTH32F_STENCIL8;
		case RHITextureFormat::DEPTH32_F32:					return GL_DEPTH_COMPONENT32F;
		case RHITextureFormat::DEPTH16_UNORM:				return GL_DEPTH_COMPONENT16;

		default:
			return 0;
		}
	}
	u32 MeteorTextureWrapToOpenGLWrap(const TextureWrap& wrap)
	{
		switch (wrap)
		{
			case TextureWrap::CLAMP:			return GL_CLAMP;
			case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
			case TextureWrap::REPEAT:			return GL_REPEAT;
			default: return 0;
		}
	}
	u32 MeteorTextureFilterToOpenGLFilter(const TextureFilter& wrap)
	{
		switch (wrap)
		{
			case TextureFilter::LINEAR:			return GL_LINEAR;
			case TextureFilter::NEAREST:		return GL_NEAREST;
			default: return 0;
		}
	}
	u32 MeteorTextureFormatToInternalFormat(u32 format)
	{
		switch (format)
		{
		case GL_RGB:
		case GL_SRGB:
		case GL_RGB8:
		case GL_SRGB8:
		case GL_RGB16:
		case GL_RGB32F:
		case GL_R11F_G11F_B10F:
			return GL_RGB;


		case GL_RGBA:
		case GL_RGBA8:
		case GL_RGBA16:
		case GL_RGBA16F:
		case GL_RGBA32F:
		case GL_RGB10_A2:
		case GL_SRGB_ALPHA:
		case GL_SRGB8_ALPHA8:
			return GL_RGBA;

		case GL_RG8: return GL_RG;
		case GL_R8: return GL_RED;

		}
	}
	OpenGLTexture2D::OpenGLTexture2D(const TextureDesc& desc, u32 width, u32 height) :
		m_texture(0),
		m_descriptor(desc),
		m_format(m_descriptor.Format),
		m_size(width, height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

		u32 dataFormat = MeteorTextureFormatToOpenGLTextureFormat(m_format, m_descriptor.IsSRGB);
		u32 internalFormat = MeteorTextureFormatToInternalFormat(dataFormat);

		glTextureStorage2D(m_texture, 1, GL_RGBA8, width, height);

		glTexParameteri(m_texture, GL_TEXTURE_WRAP_S, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));
		glTexParameteri(m_texture, GL_TEXTURE_WRAP_T, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));

		glTexParameteri(m_texture, GL_TEXTURE_MIN_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MinFilter));
		glTexParameteri(m_texture, GL_TEXTURE_MAG_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MagFilter));

		glTextureSubImage2D(m_texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	OpenGLTexture2D::OpenGLTexture2D(const TextureDesc& desc, u32 width, u32 height, u8* pointer) :
		m_texture(0),
		m_descriptor(desc),
		m_format(m_descriptor.Format),
		m_size(width, height)
	{
		BuildTexture();
	}
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path):
		m_texture(0),
		m_descriptor(RHITextureFormat::RGBA8_UNORM),
		m_format(m_descriptor.Format),
		m_size(0, 0)
    {
		ImageCore imageCore;
		if (imageCore.Load(path))
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

			u32 dataFormat = MeteorTextureFormatToOpenGLTextureFormat(m_format, m_descriptor.IsSRGB);
			u32 internalFormat = MeteorTextureFormatToInternalFormat(dataFormat);

			glTextureStorage2D(m_texture, 1, GL_RGBA8, imageCore.GetSize().x, imageCore.GetSize().y);

			glTexParameteri(m_texture, GL_TEXTURE_WRAP_S, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));
			glTexParameteri(m_texture, GL_TEXTURE_WRAP_T, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));

			glTexParameteri(m_texture, GL_TEXTURE_MIN_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MinFilter));
			glTexParameteri(m_texture, GL_TEXTURE_MAG_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MagFilter));

			glTextureSubImage2D(m_texture, 0, 0, 0, imageCore.GetSize().x, imageCore.GetSize().y, GL_RGBA, GL_UNSIGNED_BYTE, imageCore.GetPointer());
		}
    }

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const TextureDesc& desc) :
		m_texture(0),
		m_descriptor(desc),
		m_format(m_descriptor.Format),
		m_size(0, 0)
	{
		ImageCore imageCore;
		if (imageCore.Load(path))
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

			u32 dataFormat = MeteorTextureFormatToOpenGLTextureFormat(m_format, m_descriptor.IsSRGB);
			u32 internalFormat = MeteorTextureFormatToInternalFormat(dataFormat);

			glTextureStorage2D(m_texture, 1, internalFormat, imageCore.GetSize().x, imageCore.GetSize().y);

			glTexParameteri(m_texture, GL_TEXTURE_WRAP_S, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));
			glTexParameteri(m_texture, GL_TEXTURE_WRAP_T, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));

			glTexParameteri(m_texture, GL_TEXTURE_MIN_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MinFilter));
			glTexParameteri(m_texture, GL_TEXTURE_MAG_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MagFilter));

			glTextureSubImage2D(m_texture, 0, 0, 0, imageCore.GetSize().x, imageCore.GetSize().y, dataFormat, GL_UNSIGNED_BYTE, imageCore.GetPointer());
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
    void OpenGLTexture2D::UnBind(u32 slot)   const
    {
		glBindTextureUnit(slot, 0);
    }
	void OpenGLTexture2D::BuildTexture()
	{

		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

		u32 dataFormat		= MeteorTextureFormatToOpenGLTextureFormat(m_format, m_descriptor.IsSRGB);
		u32 internalFormat	= MeteorTextureFormatToInternalFormat(dataFormat);

		glTextureStorage2D(m_texture, 1, internalFormat, m_size.x, m_size.y);

		glTexParameteri(m_texture, GL_TEXTURE_WRAP_S, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));
		glTexParameteri(m_texture, GL_TEXTURE_WRAP_T, MeteorTextureWrapToOpenGLWrap(m_descriptor.WrapMode));

		glTexParameteri(m_texture, GL_TEXTURE_MIN_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MinFilter));
		glTexParameteri(m_texture, GL_TEXTURE_MAG_FILTER, MeteorTextureFilterToOpenGLFilter(m_descriptor.MagFilter));

		glTextureSubImage2D(m_texture, 0, 0, 0, m_size.x, m_size.y, dataFormat, GL_UNSIGNED_BYTE, NULL);

	}
}
