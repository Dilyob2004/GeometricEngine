#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H
#include <Engine/Render/Texture.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLTexture2D : public Texture
    {
    public:
        OpenGLTexture2D(const std::string& path);
		
        OpenGLTexture2D(const std::string& path, const TextureDesc&);
        OpenGLTexture2D(const TextureDesc&, u32, u32);
        OpenGLTexture2D(const TextureDesc&, u32, u32, u8*);


        virtual ~OpenGLTexture2D();
        virtual u32 GetTexture()	const override { return m_texture; }
        virtual void Bind(u32 slot)     const override;
        virtual void UnBind(u32 slot)   const override;


		virtual RHITextureFormat GetFormat() const override { return m_format;  }
		virtual Vector2u GetSize()	const  override { return m_size; }
    private:

		void BuildTexture();


		TextureDesc			m_descriptor;
		RHITextureFormat	m_format;
        Vector2u			m_size;
		u32					m_texture;
    };
}
#endif // OPENGLTEXTURE_H
