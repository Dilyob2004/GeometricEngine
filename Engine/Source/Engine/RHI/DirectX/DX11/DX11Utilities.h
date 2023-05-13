#ifndef DX11UTILITIES_H
#define DX11UTILITIES_H
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>

namespace GeometricEngine
{
	static D3D11_COMPARISON_FUNC EngineCompareFuncToDX11(RHICompareFunction Func)
	{
		switch (Func)
		{
			case GeometricEngine::RHICompareFunction::Less: return D3D11_COMPARISON_LESS;
			case GeometricEngine::RHICompareFunction::LessEqual:return D3D11_COMPARISON_LESS_EQUAL;
			case GeometricEngine::RHICompareFunction::Greater:return D3D11_COMPARISON_GREATER;
			case GeometricEngine::RHICompareFunction::GreaterEqual:return D3D11_COMPARISON_GREATER_EQUAL;
			case GeometricEngine::RHICompareFunction::NotEqual:return D3D11_COMPARISON_NOT_EQUAL;
			case GeometricEngine::RHICompareFunction::Never:return D3D11_COMPARISON_NEVER;
			case GeometricEngine::RHICompareFunction::Always:return D3D11_COMPARISON_ALWAYS;
		}
		return (D3D11_COMPARISON_FUNC)-1;
	}
	static D3D11_STENCIL_OP EngineDSOpToDX11(RHIDepthStencilOperation Operation)
	{
		switch (Operation)
		{
			case GeometricEngine::RHIDepthStencilOperation::Keep: return D3D11_STENCIL_OP_KEEP;
			case GeometricEngine::RHIDepthStencilOperation::Zero: return D3D11_STENCIL_OP_ZERO;
			case GeometricEngine::RHIDepthStencilOperation::Invert: return D3D11_STENCIL_OP_INVERT;
			case GeometricEngine::RHIDepthStencilOperation::Replace: return D3D11_STENCIL_OP_REPLACE;
			case GeometricEngine::RHIDepthStencilOperation::Increment: return D3D11_STENCIL_OP_INCR;
			case GeometricEngine::RHIDepthStencilOperation::SaturatedIncrement: return D3D11_STENCIL_OP_INCR_SAT;
			case GeometricEngine::RHIDepthStencilOperation::Decrement: return D3D11_STENCIL_OP_DECR;
			case GeometricEngine::RHIDepthStencilOperation::SaturatedDecrement: return D3D11_STENCIL_OP_DECR_SAT;
		}
		return (D3D11_STENCIL_OP)-1;
	}
	static D3D11_USAGE EngineUsageToDX11(RHIUsage Usage)
	{
		switch (Usage)
		{
			case GeometricEngine::RHIUsage::Immutable: return D3D11_USAGE_IMMUTABLE;
			case GeometricEngine::RHIUsage::Default: return D3D11_USAGE_DEFAULT;
			case GeometricEngine::RHIUsage::Dynamic: return D3D11_USAGE_DYNAMIC;
			case GeometricEngine::RHIUsage::Staging: return D3D11_USAGE_STAGING;
		}
		return (D3D11_USAGE)-1;
	}
	static D3D11_BLEND_OP EngineBlendOpToDX11(RHIBlendOperation Operation)
	{
		switch (Operation)
		{
			case GeometricEngine::RHIBlendOperation::Add:				return D3D11_BLEND_OP_ADD;
			case GeometricEngine::RHIBlendOperation::Substract:			return D3D11_BLEND_OP_SUBTRACT;
			case GeometricEngine::RHIBlendOperation::Min:				return D3D11_BLEND_OP_MAX;
			case GeometricEngine::RHIBlendOperation::Max:				return D3D11_BLEND_OP_MIN;
			case GeometricEngine::RHIBlendOperation::PeverseSubstract:	return D3D11_BLEND_OP_REV_SUBTRACT;
		}
		return (D3D11_BLEND_OP)-1;
	}
	static D3D11_BLEND EngineBlendToDX11(RHIBlendFactor Factor)
	{
		switch (Factor)
		{
			case GeometricEngine::RHIBlendFactor::Zero: return D3D11_BLEND_ZERO;
			case GeometricEngine::RHIBlendFactor::One:	return D3D11_BLEND_ONE;

			case GeometricEngine::RHIBlendFactor::SourceAlpha:			return D3D11_BLEND_SRC_ALPHA;
			case GeometricEngine::RHIBlendFactor::InverseSourceAlpha:	return D3D11_BLEND_INV_SRC_ALPHA;

			case GeometricEngine::RHIBlendFactor::SourceColor:			return D3D11_BLEND_SRC_COLOR;
			case GeometricEngine::RHIBlendFactor::InverseSourceColor:	return D3D11_BLEND_INV_SRC_COLOR;

			case GeometricEngine::RHIBlendFactor::DestAlpha:			return D3D11_BLEND_DEST_ALPHA;
			case GeometricEngine::RHIBlendFactor::InverseDestAlpha:		return D3D11_BLEND_INV_DEST_ALPHA;

			case GeometricEngine::RHIBlendFactor::DestColor:			return D3D11_BLEND_DEST_COLOR;
			case GeometricEngine::RHIBlendFactor::InverseDestColor:		return D3D11_BLEND_INV_DEST_COLOR;

			case GeometricEngine::RHIBlendFactor::ConstantBlendFactor:		return D3D11_BLEND_BLEND_FACTOR;
			case GeometricEngine::RHIBlendFactor::InverseConstantBlendFactor:return D3D11_BLEND_INV_BLEND_FACTOR;
		}
		return (D3D11_BLEND)-1;
	}
	static D3D11_CULL_MODE EngineCullModeToDX11(RHIRasterizerCullMode Mode)
	{
		switch (Mode)
		{
			case GeometricEngine::RHIRasterizerCullMode::None: return D3D11_CULL_NONE;
			case GeometricEngine::RHIRasterizerCullMode::Front:return D3D11_CULL_FRONT;
			case GeometricEngine::RHIRasterizerCullMode::Back:return D3D11_CULL_BACK;
		}
		return (D3D11_CULL_MODE)-1;
	}
	static D3D11_FILL_MODE EngineFillModeToDX11(RHIRasterizerFillMode Mode)
	{
		switch (Mode)
		{
			case GeometricEngine::RHIRasterizerFillMode::Solid:
			case GeometricEngine::RHIRasterizerFillMode::Point:		return D3D11_FILL_SOLID;
			case GeometricEngine::RHIRasterizerFillMode::Wireframe:	return D3D11_FILL_WIREFRAME;
		}
		return (D3D11_FILL_MODE)-1;
	}
	static D3D11_FILTER SamplerFilterEngineToDX11(RHISamplerCompareFunc Func, RHISamplerFiler Filter)
	{
		if (Func == RHISamplerCompareFunc::Never)
		{
			switch (Filter)
			{

				case GeometricEngine::RHISamplerFiler::Point:
					return D3D11_FILTER_MIN_MAG_MIP_POINT;

				case GeometricEngine::RHISamplerFiler::Bilinear:
					return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

				case GeometricEngine::RHISamplerFiler::Trilinear:
					return D3D11_FILTER_MIN_MAG_MIP_LINEAR;

				case GeometricEngine::RHISamplerFiler::Anisotropic:
					return D3D11_FILTER_ANISOTROPIC;

				default:
					break;
			}
		}
		else
		{
			switch (Filter)
			{
				case GeometricEngine::RHISamplerFiler::Point:
					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

				case GeometricEngine::RHISamplerFiler::Bilinear:
					return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;

				case GeometricEngine::RHISamplerFiler::Trilinear:
					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

				case GeometricEngine::RHISamplerFiler::Anisotropic:
					return D3D11_FILTER_COMPARISON_ANISOTROPIC;

				default:
					break;
			}
		}
		return (D3D11_FILTER)-1;
	}
	static D3D11_TEXTURE_ADDRESS_MODE SamplerAddressModeToDX11(RHISamplerAddressMode Mode)
	{
		switch (Mode)
		{
			case GeometricEngine::RHISamplerAddressMode::Wrap:
				return D3D11_TEXTURE_ADDRESS_WRAP;
			case GeometricEngine::RHISamplerAddressMode::Clamp:
				return D3D11_TEXTURE_ADDRESS_CLAMP;
			case GeometricEngine::RHISamplerAddressMode::Mirror:
				return D3D11_TEXTURE_ADDRESS_MIRROR;
			case GeometricEngine::RHISamplerAddressMode::Border:
				return D3D11_TEXTURE_ADDRESS_BORDER;
			default:
				break;
		}
		return (D3D11_TEXTURE_ADDRESS_MODE)-1;
	}

	static D3D11_PRIMITIVE_TOPOLOGY DrawTypeEngineToDX11(DrawType type)
	{
		switch (type)
		{
			case DrawType::Point:			return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
			case DrawType::Triangles:		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			case DrawType::Lines:			return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			default:						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		}
	}
	static DXGI_FORMAT EngineFormatToDX11Format(ShaderElementType type)
	{
		switch (type)
		{
			case ShaderElementType::Int:		return DXGI_FORMAT_R32_SINT;
			case ShaderElementType::Int2:		return DXGI_FORMAT_R32G32_SINT;
			case ShaderElementType::Int3:		return DXGI_FORMAT_R32G32B32_SINT;
			case ShaderElementType::Int4:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case ShaderElementType::Float:		return DXGI_FORMAT_R32_FLOAT;
			case ShaderElementType::Float2:		return DXGI_FORMAT_R32G32_FLOAT;
			case ShaderElementType::Float3:		return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderElementType::Float4:		return DXGI_FORMAT_R32G32B32A32_FLOAT;
			default:							return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}
	static RHIPixelFormat RHIFormatToDX11Format(DXGI_FORMAT Format)
	{
		switch (Format) 
		{
			case DXGI_FORMAT_R8_UINT:				return GeometricEngine::RHIPixelFormat::R8_U32;
			case DXGI_FORMAT_R8_UNORM:				return GeometricEngine::RHIPixelFormat::R8_UNORM;
			case DXGI_FORMAT_R8G8_UNORM:			return GeometricEngine::RHIPixelFormat::R8G8_UNORM;
			case DXGI_FORMAT_R8G8B8A8_UNORM:		return GeometricEngine::RHIPixelFormat::R8G8BA8_UNORM;

			case DXGI_FORMAT_R11G11B10_FLOAT:		return GeometricEngine::RHIPixelFormat::R11G11B10_F32;
			case DXGI_FORMAT_R10G10B10A2_UNORM :	return GeometricEngine::RHIPixelFormat::R10G10B10A2_UNORM;
			case DXGI_FORMAT_R32_SINT :				return GeometricEngine::RHIPixelFormat::R32_S32;
			case DXGI_FORMAT_R32G32_SINT:			return GeometricEngine::RHIPixelFormat::R32G32_S32;
			case DXGI_FORMAT_R32G32B32_SINT:		return GeometricEngine::RHIPixelFormat::R32G32B32_S32;
			case DXGI_FORMAT_R32G32B32A32_SINT:		return GeometricEngine::RHIPixelFormat::R32G32B32A32_S32;


			case DXGI_FORMAT_R32_UINT:				return GeometricEngine::RHIPixelFormat::R32_U32;
			case DXGI_FORMAT_R32G32_UINT:			return GeometricEngine::RHIPixelFormat::R32G32_U32;
			case DXGI_FORMAT_R32G32B32_UINT:		return GeometricEngine::RHIPixelFormat::R32G32B32_U32;
			case DXGI_FORMAT_R32G32B32A32_UINT:		return GeometricEngine::RHIPixelFormat::R32G32B32A32_U32;

			case DXGI_FORMAT_R16_FLOAT:				return GeometricEngine::RHIPixelFormat::R16_F32;
			case DXGI_FORMAT_R16G16_FLOAT:			return GeometricEngine::RHIPixelFormat::R16G16_F32;
			case DXGI_FORMAT_R16G16B16A16_FLOAT:	return GeometricEngine::RHIPixelFormat::R16G16B16A16_F32;
			case DXGI_FORMAT_R32_FLOAT: 			return  GeometricEngine::RHIPixelFormat::R32_F32;
			case DXGI_FORMAT_R32G32_FLOAT:			return GeometricEngine::RHIPixelFormat::R32G32_F32;
			case DXGI_FORMAT_R32G32B32_FLOAT:		return  GeometricEngine::RHIPixelFormat::R32G32B32_F32;
			case DXGI_FORMAT_R32G32B32A32_FLOAT:	return  GeometricEngine::RHIPixelFormat::R32G32B32A32_F32;


			case DXGI_FORMAT_D16_UNORM:				return  GeometricEngine::RHIPixelFormat::DEPTH16_UNORM;
			case DXGI_FORMAT_D32_FLOAT:				return GeometricEngine::RHIPixelFormat::DEPTH32_F32;
			case DXGI_FORMAT_D24_UNORM_S8_UINT:		return GeometricEngine::RHIPixelFormat::DEPTH24_UNORM_STENCIL8_U32;
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:  return GeometricEngine::RHIPixelFormat::DEPTH32_F32_STENCIL8_U32;

		}
		return RHIPixelFormat::NONE;
	}
	static DXGI_FORMAT RHIFormatToDX11Format(RHIPixelFormat Format)
	{
		switch (Format)
		{
			case GeometricEngine::RHIPixelFormat::NONE:
				break;

			case GeometricEngine::RHIPixelFormat::R8_U32:				return DXGI_FORMAT_R8_UINT;
			case GeometricEngine::RHIPixelFormat::R8_UNORM:				return DXGI_FORMAT_R8_UNORM;
			case GeometricEngine::RHIPixelFormat::R8G8_UNORM:			return DXGI_FORMAT_R8G8_UNORM;
			case GeometricEngine::RHIPixelFormat::R8G8BA8_UNORM:		return DXGI_FORMAT_R8G8B8A8_UNORM;

			case GeometricEngine::RHIPixelFormat::R11G11B10_F32:		return DXGI_FORMAT_R11G11B10_FLOAT;
			case GeometricEngine::RHIPixelFormat::R10G10B10A2_UNORM:	return DXGI_FORMAT_R10G10B10A2_UNORM;
			case GeometricEngine::RHIPixelFormat::R32_S32:				return DXGI_FORMAT_R32_SINT;
			case GeometricEngine::RHIPixelFormat::R32G32_S32:			return DXGI_FORMAT_R32G32_SINT;
			case GeometricEngine::RHIPixelFormat::R32G32B32_S32:		return DXGI_FORMAT_R32G32B32_SINT;
			case GeometricEngine::RHIPixelFormat::R32G32B32A32_S32:		return DXGI_FORMAT_R32G32B32A32_SINT;


			case GeometricEngine::RHIPixelFormat::R32_U32:				return DXGI_FORMAT_R32_UINT;
			case GeometricEngine::RHIPixelFormat::R32G32_U32:			return DXGI_FORMAT_R32G32_UINT;
			case GeometricEngine::RHIPixelFormat::R32G32B32_U32:		return DXGI_FORMAT_R32G32B32_UINT;
			case GeometricEngine::RHIPixelFormat::R32G32B32A32_U32:		return DXGI_FORMAT_R32G32B32A32_UINT;

			case GeometricEngine::RHIPixelFormat::R16_F32:				return DXGI_FORMAT_R16_FLOAT;
			case GeometricEngine::RHIPixelFormat::R16G16_F32:			return DXGI_FORMAT_R16G16_FLOAT;
			case GeometricEngine::RHIPixelFormat::R16G16B16A16_F32:		return DXGI_FORMAT_R16G16B16A16_FLOAT;
			case GeometricEngine::RHIPixelFormat::R32_F32: 				return DXGI_FORMAT_R32_FLOAT;
			case GeometricEngine::RHIPixelFormat::R32G32_F32:			return DXGI_FORMAT_R32G32_FLOAT;
			case GeometricEngine::RHIPixelFormat::R32G32B32_F32:		return DXGI_FORMAT_R32G32B32_FLOAT;
			case GeometricEngine::RHIPixelFormat::R32G32B32A32_F32:		return DXGI_FORMAT_R32G32B32A32_FLOAT;

				 
			case GeometricEngine::RHIPixelFormat::DEPTH16_UNORM: return DXGI_FORMAT_D16_UNORM;
			case GeometricEngine::RHIPixelFormat::DEPTH32_F32: return DXGI_FORMAT_D32_FLOAT;
			case GeometricEngine::RHIPixelFormat::DEPTH24_UNORM_STENCIL8_U32: return DXGI_FORMAT_D24_UNORM_S8_UINT;
			case GeometricEngine::RHIPixelFormat::DEPTH32_F32_STENCIL8_U32: ; return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		}

		return (DXGI_FORMAT)-1;
	}
}
#endif // !DX11UTILITIES_H
