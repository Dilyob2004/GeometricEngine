#ifndef RHIUTILITIES_H
#define RHIUTILITIES_H

#include <Engine/Core/Config.h>
namespace GeometricEngine
{

	enum class RHIPixelFormat : U32
	{
		NONE = 0,

		R8_UNORM,
		R8G8_UNORM,
		R8G8BA8_UNORM,

		R8_U32,

		R11G11B10_F32,
		R10G10B10A2_UNORM,

		R32_S32,
		R32G32_S32,
		R32G32B32_S32,
		R32G32B32A32_S32,

		R32_U32,
		R32G32_U32,
		R32G32B32_U32,
		R32G32B32A32_U32,

		R16_F32,
		R16G16_F32,
		R16G16B16A16_F32,

		R32_F32,
		R32G32_F32,
		R32G32B32_F32,
		R32G32B32A32_F32,

		DEPTH16_UNORM,
		DEPTH32_F32,

		DEPTH24_UNORM_STENCIL8_U32,
		DEPTH32_F32_STENCIL8_U32
	};
	enum class BlendMode
	{
		None = 0,
		OneZero,
		ZeroSrcColor,
		SrcAlphaOneMinusSrcAlpha,
	};
	enum class ShaderElementType
	{
		Int, Int2, Int3, Int4,
		Mat, Mat2, Mat3, Mat4,
		Float, Float2, Float3, Float4,
		None
	};
	enum class RHISamplerFiler
	{
		Point,
		Bilinear,
		Trilinear,
		Anisotropic,
	};
	enum class RHISamplerAddressMode
	{
		Wrap,
		Clamp,
		Mirror,
		Border
	};
	enum class RHISamplerCompareFunc
	{
		Never,
		Less
	};
	enum class RHIBlendOperation
	{
		Add,
		Substract,
		Min,
		Max,
		PeverseSubstract
	};
	enum class RHIBlendFactor
	{
		Zero,
		One,
		SourceAlpha,
		InverseSourceAlpha,
		SourceColor,
		InverseSourceColor,
		DestAlpha,
		InverseDestAlpha,
		DestColor,
		InverseDestColor,
		ConstantBlendFactor,
		InverseConstantBlendFactor,
	};
	enum RHIRenderTargetWriteMask : U32
	{
		RTWM_RED = 1,
		RTWM_GREEN = 2,
		RTWM_BLUE = 4,
		RTWM_ALPHA = 8,
		RTWM_RGBA = RTWM_RED | RTWM_GREEN | RTWM_BLUE | RTWM_ALPHA,
		RTWM_RGB = RTWM_RED | RTWM_GREEN | RTWM_BLUE
	};
	enum class RHIRasterizerFillMode
	{
		Point,
		Wireframe,
		Solid
	};
	enum class RHIRasterizerCullMode
	{
		None,
		Front,
		Back
	};
	enum class RHISamplerBorderColor
	{
		Transparent,
		OpaqueBlack,
		OpaqueWhite
	};
	enum class RHICompareFunction
	{
		Less,
		LessEqual,
		Greater,
		GreaterEqual,
		NotEqual,
		Never,
		Always
	};
	enum class RHIDepthStencilOperation
	{
		Keep,
		Zero,
		Invert,
		Replace,
		Increment,
		SaturatedIncrement,
		Decrement,
		SaturatedDecrement,
	};

	enum class DrawType
	{
		Point,
		Triangles,
		Lines
	};

	enum RHITextureFlags : U32
	{
		TF_None = 0U,
		TF_ShaderResource = 1U,
		TF_DepthStencil = 2U,
		TF_RenderTarget = 4U
	};
	enum class RHITextureUsage
	{
		Immutable,
		Default,
		Dynamic,
		Staging
	};
}

#endif