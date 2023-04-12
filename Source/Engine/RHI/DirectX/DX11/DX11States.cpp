
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/Core/Misc/Log.h>

namespace GeometricEngine
{
	DX11SamplerState::DX11SamplerState()
		: DXSamplerState(NULL)
	{

	}
	DX11SamplerState::DX11SamplerState(ID3D11SamplerState* Sampler)
		: DXSamplerState(Sampler)
	{
	}
	DX11SamplerState::~DX11SamplerState()
	{
		DXSamplerState->Release();
	}


	DX11RasterizerState::DX11RasterizerState()
		: DXRasterizerState(NULL)
	{

	}
	DX11RasterizerState::DX11RasterizerState(ID3D11RasterizerState* RasterizerState)
		: DXRasterizerState(RasterizerState)
	{

	}
	DX11RasterizerState::~DX11RasterizerState()
	{
		DXRasterizerState->Release();
	}

	DX11BlendState::DX11BlendState()
		: DXBlendState(NULL)
	{

	}
	DX11BlendState::DX11BlendState(ID3D11BlendState* BlendState)
		: DXBlendState(BlendState)
	{
	}
	DX11BlendState::~DX11BlendState()
	{
		DXBlendState->Release();
	}

	DX11DepthStencilState::DX11DepthStencilState()
		: DXDepthStencilState(NULL)
	{

	}
	DX11DepthStencilState::DX11DepthStencilState(ID3D11DepthStencilState* DepthStencilState)
		: DXDepthStencilState(DepthStencilState)
	{

	}
	DX11DepthStencilState::~DX11DepthStencilState()
	{
		DXDepthStencilState->Release();
	}
	RHIDepthStencilState* DX11DynamicRHI::RHICreateDepthStencilState(const RHIDepthStencilStateDefinition& Definition)
	{
		D3D11_DEPTH_STENCIL_DESC DepthStecilDesc;
		SMemory::Zero(&DepthStecilDesc, sizeof(DepthStecilDesc));
		DepthStecilDesc.DepthEnable = true;

		if (Definition.EnabledDepthWrite)
			DepthStecilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		else
			DepthStecilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		DepthStecilDesc.DepthFunc = EngineCompareFuncToDX11(Definition.DepthTest);
		DepthStecilDesc.StencilEnable = Definition.EnabledBackFaceStencil | Definition.EnabledFrontFaceStencil;
		DepthStecilDesc.StencilReadMask = Definition.StencilReadMask;
		DepthStecilDesc.StencilWriteMask = Definition.StencilWriteMask;

		DepthStecilDesc.FrontFace.StencilFunc = EngineCompareFuncToDX11(Definition.FFStencilTest);
		DepthStecilDesc.FrontFace.StencilFailOp = EngineDSOpToDX11(Definition.FFStencilFailOp);
		DepthStecilDesc.FrontFace.StencilDepthFailOp = EngineDSOpToDX11(Definition.FFDepthFailOp);
		DepthStecilDesc.FrontFace.StencilPassOp = EngineDSOpToDX11(Definition.FFPassFailOp);

		if (Definition.EnabledBackFaceStencil)
		{
			DepthStecilDesc.BackFace.StencilFunc = EngineCompareFuncToDX11(Definition.BFStencilTest);
			DepthStecilDesc.BackFace.StencilFailOp = EngineDSOpToDX11(Definition.BFStencilFailOp);
			DepthStecilDesc.BackFace.StencilDepthFailOp = EngineDSOpToDX11(Definition.BFDepthFailOp);
			DepthStecilDesc.BackFace.StencilPassOp = EngineDSOpToDX11(Definition.BFPassFailOp);
		}
		else
		{
			DepthStecilDesc.BackFace = DepthStecilDesc.FrontFace;
		}

		ID3D11DepthStencilState* DepthStencilState;
		if (FAILED(GetDXDevice()->CreateDepthStencilState(&DepthStecilDesc, &DepthStencilState)))
		{
			LOG("Error: [DX11RHI] Failed to create a Blend state!");
			exit(-1);
		}
		return new DX11DepthStencilState(DepthStencilState);
	}
	RHIBlendState* DX11DynamicRHI::RHICreateBlendState(const RHIBlendStateDefinition& Definition)
	{
		D3D11_BLEND_DESC BlendDesc;
		SMemory::Zero(&BlendDesc, sizeof(BlendDesc));

		BlendDesc.AlphaToCoverageEnable = true;
		BlendDesc.IndependentBlendEnable = Definition.EnabledIndependentBlend;


		D3D11_RENDER_TARGET_BLEND_DESC& RenderTarget = BlendDesc.RenderTarget[0];
		RenderTarget.BlendEnable	= true;

		RenderTarget.SrcBlend		= EngineBlendToDX11(Definition.RenderTarget.ColorBlendSrc);
		RenderTarget.DestBlend		= EngineBlendToDX11(Definition.RenderTarget.ColorBlendDest);
		RenderTarget.BlendOp		= EngineBlendOpToDX11(Definition.RenderTarget.ColorBlendOperation);

		RenderTarget.SrcBlendAlpha	= EngineBlendToDX11(Definition.RenderTarget.AlphaBlendSrc);
		RenderTarget.DestBlendAlpha = EngineBlendToDX11(Definition.RenderTarget.AlphaBlendDest);
		RenderTarget.BlendOpAlpha	= EngineBlendOpToDX11(Definition.RenderTarget.AlphaBlendOperation);

		if (Definition.RenderTarget.ColorWriteMask & RTWM_RED)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_RED;

		if (Definition.RenderTarget.ColorWriteMask & RTWM_GREEN)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_GREEN;

		if (Definition.RenderTarget.ColorWriteMask & RTWM_BLUE)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_BLUE;

		if (Definition.RenderTarget.ColorWriteMask & RTWM_ALPHA)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
		ID3D11BlendState* BlendState;
		if (FAILED(GetDXDevice()->CreateBlendState(&BlendDesc, &BlendState)))
		{
			LOG("Error: [DX11RHI] Failed to create a Blend state!");
			exit(-1);
		}
		return new DX11BlendState(BlendState);
	}
	RHISamplerState* DX11DynamicRHI::RHICreateSamplerState(const RHISamplerStateDefinition& Definition)
	{
		D3D11_SAMPLER_DESC SamplerDesc;
		SMemory::Zero(&SamplerDesc, sizeof(SamplerDesc));
		SamplerDesc.AddressU = SamplerAddressModeToDX11(Definition.AddressModeU);
		SamplerDesc.AddressV = SamplerAddressModeToDX11(Definition.AddressModeV);
		SamplerDesc.AddressW = SamplerAddressModeToDX11(Definition.AddressModeW);
		SamplerDesc.Filter = SamplerFilterEngineToDX11(Definition.SamplerComarisonFunc, Definition.Filter);
		SamplerDesc.ComparisonFunc = (Definition.SamplerComarisonFunc == RHISamplerCompareFunc::Never)
			? D3D11_COMPARISON_NEVER : D3D11_COMPARISON_LESS;

		SamplerDesc.MipLODBias = Definition.MipBias;
		SamplerDesc.MaxAnisotropy = Definition.MaxAnisotropy;
		SamplerDesc.MinLOD = Definition.MinLod;
		SamplerDesc.MaxLOD = Definition.MaxLod;

		switch (Definition.BorderColor)
		{
		case RHISamplerBorderColor::Transparent:
			SamplerDesc.BorderColor[0] = SamplerDesc.BorderColor[1] =
				SamplerDesc.BorderColor[2] = SamplerDesc.BorderColor[3] = 0.0f;
			break;

		case RHISamplerBorderColor::OpaqueWhite:
			SamplerDesc.BorderColor[0] = SamplerDesc.BorderColor[1] =
				SamplerDesc.BorderColor[2] = SamplerDesc.BorderColor[3] = 1.0f;
			break;

		case RHISamplerBorderColor::OpaqueBlack:
			SamplerDesc.BorderColor[0] = 0.0f;
			SamplerDesc.BorderColor[1] = 0.0f;
			SamplerDesc.BorderColor[2] = 0.0f;
			SamplerDesc.BorderColor[3] = 1.0f;
			break;
		}
		ID3D11SamplerState* DXSamplerState;
		if (FAILED(GetDXDevice()->CreateSamplerState(&SamplerDesc, &DXSamplerState)))
		{
			LOG("Error: [DX11RHI] Failed to create a sampler state!");
			exit(-1);
		}
		return new DX11SamplerState(DXSamplerState);
	}
	RHIRasterizerState* DX11DynamicRHI::RHICreateRasterizerState(const RHIRasterizerStateDefinition& Definition)
	{
		D3D11_RASTERIZER_DESC RasterizerDesc;
		SMemory::Zero(&RasterizerDesc, sizeof(RasterizerDesc));
		RasterizerDesc.CullMode = EngineCullModeToDX11(Definition.CullMode);
		RasterizerDesc.FillMode = EngineFillModeToDX11(Definition.FillMode);
		RasterizerDesc.ScissorEnable = false;
		RasterizerDesc.DepthClipEnable = true;
		RasterizerDesc.FrontCounterClockwise = true;
		RasterizerDesc.DepthBias = (INT) Definition.DepthBias;
		RasterizerDesc.MultisampleEnable = Definition.EnableMSAA;
		RasterizerDesc.SlopeScaledDepthBias = Definition.SlopeScaleDepthBias;

		ID3D11RasterizerState* DXRasterizerState;

		if (FAILED(GetDXDevice()->CreateRasterizerState(&RasterizerDesc, &DXRasterizerState)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Rasterizer State!");
			exit(-1);
		}
		return new DX11RasterizerState(DXRasterizerState);
	}

}