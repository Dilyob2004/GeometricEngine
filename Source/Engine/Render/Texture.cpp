#include <Engine/Render/Texture.h>
#include <Engine/Render/OpenGL/OpenGLTexture.h>
namespace MeteorEngine
{
    Texture2D * Texture2D::Create(const std::string& path)
    {
        return new OpenGLTexture2D(path);
    }
    Texture2D * Texture2D::Create(const TextureDesc& desc, u32 width, u32 height)
    {
        return new OpenGLTexture2D( desc, width, height);
    }

	Texture2D* Texture2D::Create(const std::string& path, const TextureDesc& desc)
	{
		return new OpenGLTexture2D(path, desc);
	}
	Texture2D* Texture2D::Create(const TextureDesc& desc, u32 width, u32 height, u8* data)
	{
		return new OpenGLTexture2D(desc, width, height, data);
	}
}
