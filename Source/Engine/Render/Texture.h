#ifndef TEXTURE_H
#define TEXTURE_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
#include <string>
namespace MeteorEngine
{
	enum class RHITextureFormat : u32
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
	enum class TextureFilter
	{
		NONE,
		LINEAR,
		NEAREST
	};

	struct TextureDesc
	{
		TextureDesc() = default;
		TextureDesc(const RHITextureFormat & format, const TextureFilter& minFilter = TextureFilter::LINEAR, 
					const TextureFilter& magFilter = TextureFilter::LINEAR, const TextureWrap& wrapMode = TextureWrap::CLAMP, bool isSRGB = false):
			Format(format),
			MinFilter(minFilter),
			MagFilter(magFilter),
			WrapMode(wrapMode),
			IsSRGB(isSRGB)
		{
		}
		RHITextureFormat Format;
		TextureFilter MinFilter;
		TextureFilter MagFilter;
		TextureWrap WrapMode;
		bool IsSRGB;
	};
    class METEOR_API Texture
    {
    public:
        virtual ~Texture() {}
        virtual u32			GetTexture() const = 0;
        virtual void        Bind(u32 slot = 0) const = 0;
        virtual void        UnBind(u32 slot = 0)    const = 0;


		virtual RHITextureFormat GetFormat() const = 0;
		virtual Vector2u GetSize()	const = 0;

		static bool IsDepthStencilFormat(RHITextureFormat format)
		{
			return (format == RHITextureFormat::DEPTH16_UNORM_STENCIL8_U32 ||
					format == RHITextureFormat::DEPTH24_UNORM_STENCIL8_U32 ||
					format == RHITextureFormat::DEPTH32_F32_STENCIL8_U32);
		}		
		static bool IsDepthFormat(RHITextureFormat format)
		{
			return (format == RHITextureFormat::DEPTH16_UNORM ||
					format == RHITextureFormat::DEPTH32_F32   ||
					format == RHITextureFormat::DEPTH16_UNORM_STENCIL8_U32 ||
					format == RHITextureFormat::DEPTH32_F32_STENCIL8_U32);
		}
		static bool IsStencilFormat(RHITextureFormat format)
		{
			return IsDepthStencilFormat(format);
		}
    };
    class METEOR_API Texture2D: public Texture
    {
    public:
        static Texture2D*	Create(const std::string& );
		static Texture2D*	Create(const TextureDesc&, u32, u32);


		static Texture2D*	Create(const std::string&, const TextureDesc&);
		static Texture2D*	Create(const TextureDesc&, u32, u32, u8*);
    };
}
#endif // TEXTURE_H
