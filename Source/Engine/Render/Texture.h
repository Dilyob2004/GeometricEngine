#ifndef TEXTURE_H
#define TEXTURE_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
#include <string>
namespace MeteorEngine
{
	struct TextureDesc
	{
		TextureDesc() = default;
		TextureDesc(const RHIPixelFormat& format, const TextureFilter& minFilter = TextureFilter::LINEAR,
			const TextureFilter& magFilter = TextureFilter::LINEAR, const TextureWrap& wrapMode = TextureWrap::CLAMP, bool isSRGB = false) :
			Format(format),
			MinFilter(minFilter),
			MagFilter(magFilter),
			WrapMode(wrapMode),
			IsSRGB(isSRGB)
		{
		}
		u16				Flags = TextureFlags::Texture_CreateMips;
		u16				MsaaLevel = 1;
		RHIPixelFormat	Format = RHIPixelFormat::RGB8_UNORM;
		TextureFilter	MinFilter = TextureFilter::NEAREST;
		TextureFilter	MagFilter = TextureFilter::NEAREST;
		TextureWrap		WrapMode = TextureWrap::CLAMP_TO_EDGE;
		bool			IsSRGB = false;
	};
    class METEOR_API Texture
    {
    public:
        virtual ~Texture() {}
		virtual void*		GetTextureHande() const = 0;
        virtual void*		GetTexture() const = 0;
        virtual void        Bind(u32 slot = 0) const = 0;
        virtual void        UnBind(u32 slot = 0)    const = 0;


		virtual RHIPixelFormat GetFormat() const = 0;
		virtual Vector2u GetSize()	const = 0;
		virtual TextureType GetType()	const = 0;

		static bool IsDepthStencilFormat(RHIPixelFormat format)
		{
			return (format == RHIPixelFormat::DEPTH16_UNORM_STENCIL8_U32 ||
					format == RHIPixelFormat::DEPTH24_UNORM_STENCIL8_U32 ||
					format == RHIPixelFormat::DEPTH32_F32_STENCIL8_U32);
		}		
		static bool IsDepthFormat(RHIPixelFormat format)
		{
			return (format == RHIPixelFormat::DEPTH16_UNORM ||
					format == RHIPixelFormat::DEPTH32_F32   ||
					format == RHIPixelFormat::DEPTH16_UNORM_STENCIL8_U32 ||
					format == RHIPixelFormat::DEPTH32_F32_STENCIL8_U32);
		}
		static bool IsStencilFormat(RHIPixelFormat format)
		{
			return IsDepthStencilFormat(format);
		}
	protected:
		u16			m_Flags = 0;

    };
	class METEOR_API Texture2D : public Texture
	{
	public:
		static Texture2D* Create(const std::string& , const TextureDesc& desc = TextureDesc());
		static Texture2D* Create(const TextureDesc&, const Vector2u&);
		virtual void Resize(const Vector2u&) = 0;
	};
	class METEOR_API TextureDepth : public Texture
	{
	public:
		static TextureDepth* Create(const Vector2u&);
		virtual void Resize(const Vector2u&) = 0;
	};
	class METEOR_API TextureDepthArray : public Texture
	{
	public:
		static TextureDepthArray* Create(u32, u32, u32);
		virtual void Resize(u32, u32) = 0;
	};
}
#endif // TEXTURE_H
