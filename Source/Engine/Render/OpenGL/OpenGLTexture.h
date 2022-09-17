#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H
#include <Engine/Render/Texture.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();
        virtual u32 GetTexture() const;
        virtual Vector2u GetSize()   const override { return m_size; }
        virtual void Bind(u32 slot)     const override;
        virtual void UnBind(u32 slot)   const override;

    private:
        Vector2u m_size;
		u32 m_texture;
    };
}
#endif // OPENGLTEXTURE_H
