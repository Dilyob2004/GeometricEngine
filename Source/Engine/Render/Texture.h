#ifndef TEXTURE_H
#define TEXTURE_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
#include <string>
namespace MeteorEngine
{
	enum class RHIPixelFormat : u32
	{
		NONE = 0,

		R8_UNORM,
		RG8_UNORM,
		RGB8_UNORM,
		RGBA8_UNORM,

		R8_U32,

		RG11B10_F32,
		RGB10A2_UNORM,

		R32_S32,
		RG32_S32,
		RGB32_S32,
		RGBA32_S32,

		R32_U32,
		RG32_U32,
		RGB32_U32,
		RGBA32_U32,

		R16_F32,
		RG16_F32,
		RGB16_F32,
		RGBA16_F32,

		R32_F32,
		RG32_F32,
		RGB32_F32,
		RGBA32_F32,

		DEPTH16_UNORM,
		DEPTH32_F32,

		DEPTH16_UNORM_STENCIL8_U32,
		DEPTH24_UNORM_STENCIL8_U32,
		DEPTH32_F32_STENCIL8_U32
	};
	enum class TextureWrap
	{
		NONE,
		REPEAT,
		CLAMP,
		CLAMP_TO_EDGE
	};
	enum class TextureType
	{
		COLOR,
		DEPTH
	};
	enum class TextureFilter
	{
		NONE,
		LINEAR,
		NEAREST
	};
	enum TextureFlags : u16
	{
		Texture_Sampled					= (0),
		Texture_Storage					= (1),
		Texture_RenderTarget			= (2),
		Texture_DepthStencil			= (3),
		Texture_DepthStencilReadOnly	= (4),
		Texture_CreateMips				= (5),
		Texture_MipViews				= (6)
	};
	struct TextureDesc
	{
		TextureDesc() = default;
		TextureDesc(const RHIPixelFormat & format, const TextureFilter& minFilter = TextureFilter::LINEAR, 
					const TextureFilter& magFilter = TextureFilter::LINEAR, const TextureWrap& wrapMode = TextureWrap::CLAMP, bool isSRGB = false):
			Format(format),
			MinFilter(minFilter),
			MagFilter(magFilter),
			WrapMode(wrapMode),
			IsSRGB(isSRGB)
		{
		}
		u16				Flags		= TextureFlags::Texture_CreateMips;
		u16				MsaaLevel	= 1;
		RHIPixelFormat	Format		= RHIPixelFormat::RGB8_UNORM;
		TextureFilter	MinFilter	= TextureFilter::NEAREST;
		TextureFilter	MagFilter	= TextureFilter::NEAREST;
		TextureWrap		WrapMode	= TextureWrap::CLAMP_TO_EDGE;
		bool			IsSRGB		= false;
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
		static TextureDepth* Create(u32, u32, u32);
		virtual void Resize(u32, u32) = 0;
	};
}
#endif // TEXTURE_H
