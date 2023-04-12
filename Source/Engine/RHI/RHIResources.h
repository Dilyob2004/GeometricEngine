#ifndef RHIVIEWPORT_H
#define RHIVIEWPORT_H
#include "RHIUtilities.h"
#include <Engine/Core/Misc/StringView.h>
#include <Engine/Core/Containers/Array.h>
namespace GeometricEngine
{

	struct RHIViewportDefinition
	{
		RHIViewportDefinition()
			: Width(800)
			, Height(600)
			, Format(RHIPixelFormat::R8G8BA8_UNORM)
			, RefreshRateNum(60)
			, FullScreen(false)
			, VSync(true)
			, HandleWindow(NULL)
		{
		}
		U32 Width;
		U32 Height;
		U32 RefreshRateNum;
		bool FullScreen;
		bool VSync;
		RHIPixelFormat Format;
		void* HandleWindow;
	};

	struct RHIRasterizerStateDefinition
	{
		RHIRasterizerStateDefinition()
			: FillMode(RHIRasterizerFillMode::Solid)
			, CullMode(RHIRasterizerCullMode::None)
			, DepthBias(0)
			, SlopeScaleDepthBias(0)
			, EnableMSAA(true)
			, EnableLineAA(false)
		{
		}
		RHIRasterizerFillMode FillMode;
		RHIRasterizerCullMode CullMode;
		float DepthBias;
		float SlopeScaleDepthBias;
		bool EnableMSAA;
		bool EnableLineAA;
	};
	struct RHIBlendStateDefinition
	{

		struct Attachment
		{
			Attachment()
				: ColorBlendOperation(RHIBlendOperation::Add)
				, ColorBlendSrc(RHIBlendFactor::SourceAlpha)
				, ColorBlendDest(RHIBlendFactor::InverseSourceAlpha)

				, AlphaBlendOperation(RHIBlendOperation::Add)
				, AlphaBlendSrc(RHIBlendFactor::One)
				, AlphaBlendDest(RHIBlendFactor::InverseSourceAlpha)

				, ColorWriteMask(RTWM_RGBA)
			{
			}
			RHIBlendOperation ColorBlendOperation;
			RHIBlendFactor ColorBlendSrc;
			RHIBlendFactor ColorBlendDest;
			RHIBlendOperation AlphaBlendOperation;
			RHIBlendFactor AlphaBlendSrc;
			RHIBlendFactor AlphaBlendDest;
			RHIRenderTargetWriteMask ColorWriteMask;
		};
		RHIBlendStateDefinition() 
			: RenderTarget()
			, EnabledIndependentBlend(false)
		{
		}
		RHIBlendStateDefinition(const Attachment& ColorAttachment)
		{
			RenderTarget = ColorAttachment;
			EnabledIndependentBlend = false;
		}


		bool EnabledIndependentBlend;
		Attachment RenderTarget;
	};
	struct RHIDepthStencilStateDefinition
	{
		RHIDepthStencilStateDefinition()
			: EnabledDepthWrite(true)
			, DepthTest(RHICompareFunction::LessEqual)
			, EnabledFrontFaceStencil(false)
			, FFStencilTest(RHICompareFunction::Always)
			, FFStencilFailOp(RHIDepthStencilOperation::Keep)
			, FFDepthFailOp(RHIDepthStencilOperation::Keep)
			, FFPassFailOp(RHIDepthStencilOperation::Keep)
			, EnabledBackFaceStencil(false)
			, BFStencilTest(RHICompareFunction::Always)
			, BFStencilFailOp(RHIDepthStencilOperation::Keep)
			, BFDepthFailOp(RHIDepthStencilOperation::Keep)
			, BFPassFailOp(RHIDepthStencilOperation::Keep)
			, StencilReadMask(0xFF)
			, StencilWriteMask(0xFF)
		{
		}
		bool EnabledDepthWrite;
		RHICompareFunction DepthTest;

		bool EnabledFrontFaceStencil;
		RHICompareFunction FFStencilTest;
		RHIDepthStencilOperation FFStencilFailOp;
		RHIDepthStencilOperation FFDepthFailOp;
		RHIDepthStencilOperation FFPassFailOp;

		bool EnabledBackFaceStencil;
		RHICompareFunction BFStencilTest;
		RHIDepthStencilOperation BFStencilFailOp;
		RHIDepthStencilOperation BFDepthFailOp;
		RHIDepthStencilOperation BFPassFailOp;

		U8 StencilReadMask;
		U8 StencilWriteMask;
	};
	struct RHISamplerStateDefinition
	{
		RHISamplerStateDefinition()
			: MinLod(-FLT_MAX)
			, MaxLod(FLT_MAX)
			, MipBias(0)
			, MaxAnisotropy(0)
			, Filter(RHISamplerFiler::Trilinear)
			, AddressModeU(RHISamplerAddressMode::Wrap)
			, AddressModeV(RHISamplerAddressMode::Wrap)
			, AddressModeW(RHISamplerAddressMode::Wrap)
			, BorderColor(RHISamplerBorderColor::OpaqueWhite)
			, SamplerComarisonFunc(RHISamplerCompareFunc::Never)
		{
		}
		F32 MinLod;
		F32 MaxLod;
		F32 MipBias;
		I32 MaxAnisotropy;
		RHISamplerFiler Filter;
		RHISamplerAddressMode AddressModeU;
		RHISamplerAddressMode AddressModeV;
		RHISamplerAddressMode AddressModeW;
		RHISamplerBorderColor BorderColor;
		RHISamplerCompareFunc SamplerComarisonFunc;
	};

	struct RHITextureDefinition
	{
		RHITextureDefinition()
			: Width(1)
			, Height(1)
			, Data(NULL)
			, Samples(1)
			, MipLevels(1)
			, Usage(RHITextureUsage::Default)
			, Format(RHIPixelFormat::R8G8BA8_UNORM)
			, Flags(-1)
		{
		}
		U32 Width;
		U32 Height;
		U32 MipLevels;
		U32 Samples;
		U8* Data;
		RHITextureUsage Usage;
		RHIPixelFormat Format;
		U32 Flags;
	};
	struct BufferElement
	{
		BufferElement()
			: BufferName("")
			, BufferType(ShaderElementType::None)
		{
		}
		BufferElement(const StringView& Name, ShaderElementType Type)
			: BufferName(Name)
			, BufferType(Type)
		{
		}
		StringView			BufferName;
		ShaderElementType	BufferType;
	};

	class RHITexture
	{
	public:
		RHITexture()
			: NumMipmaps(1)
			, NumSamples(0)
			, Format(RHIPixelFormat::NONE)
			, Flags(TF_None)
		{
		}
		RHITexture(U32 Mipmaps, U32 Samples, RHIPixelFormat EFormat, U32 EFlags)
			: NumMipmaps(Mipmaps)
			, NumSamples(Samples)
			, Format(EFormat)
			, Flags(EFlags)
		{
		}
		virtual ~RHITexture() {}
		U32 GetNumMipmaps() const { return NumMipmaps; }
		U32 GetNumSamples() const { return NumSamples; }
		RHIPixelFormat GetFormat() const { return Format; }
		U32 GetFlags() const { return Flags; }

	private:
		U32 NumMipmaps, NumSamples;
		RHIPixelFormat Format;
		U32 Flags;
	};
	class RHITexture2D : public RHITexture
	{
	public:
		RHITexture2D()
			: RHITexture()
			, Width(0)
			, Height(0)
		{
		}
		RHITexture2D(U32 UWidth, U32 UHeight, U32 Mipmaps, U32 Samples, RHIPixelFormat EFormat, U32 EFlags) 
			: RHITexture(Mipmaps, Samples, EFormat, EFlags)
			, Width(UWidth)
			, Height(UHeight)
		{
		}

		virtual void SafeRelease() { }
		U32 GetWidth() const { return Width; }
		U32 GetHeight() const { return Height; }
		virtual void* GetHandle() { return NULL; }
	private:
		U32 Width, Height;
	};
	class RHIViewport { public: virtual ~RHIViewport(){} };

	class RHIPixelShader { public: virtual ~RHIPixelShader() {} };
	class RHIVertexShader { public: virtual ~RHIVertexShader() {} };
	class RHIVertexLayout { public: virtual ~RHIVertexLayout() {} };

	class RHIVertexBuffer { public: virtual ~RHIVertexBuffer() {} };
	class RHIIndexBuffer { public: virtual ~RHIIndexBuffer() {} };
	class RHIConstantBuffer { public: virtual ~RHIConstantBuffer() {} };

	class RHIBlendState { public: virtual ~RHIBlendState() {} };
	class RHIDepthStencilState { public: virtual ~RHIDepthStencilState() {} };
	class RHISamplerState { public: virtual ~RHISamplerState() {} };
	class RHIRasterizerState { public: virtual ~RHIRasterizerState() {} };

							
}
#endif // !RHIVIEWPORT_H
