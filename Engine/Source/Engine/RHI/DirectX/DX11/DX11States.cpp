
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Misc/String.h>

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
	
RHIPipelineState* DX11DynamicRHI::RHICreatePipelineState(const RHIPipelineStateDefinition& Definition)
{
	DYNAMIC_CAST(DX11VertexShader, VertexShader, Definition.VertexShader);
	DYNAMIC_CAST(DX11PixelShader, PixelShader, Definition.PixelShader);

	ID3D11InputLayout* DXInputLayout;
	{
		TArray<D3D11_INPUT_ELEMENT_DESC> InputElementsDescriptor;

		for (auto Element : Definition.VertexParameters)
		{
			InputElementsDescriptor.Push({ *(Element.BufferName), 0, EngineFormatToDX11Format(Element.BufferType), 0,
											(Element == Definition.VertexParameters.First()) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		}
		if (FAILED(DXDevice->CreateInputLayout(InputElementsDescriptor.Pointer(),
			InputElementsDescriptor.Count(),
			VertexShader->GetCode().Pointer(),
			VertexShader->GetCode().Count(),
			&DXInputLayout)))

		{
			LOG("Error: [DX11RHI] Failed to Create a InputLayout!");
			exit(-1);
		}
	}
		
	ID3D11BlendState* DXBlendState = NULL;
	{
		RHIBlendStateDefinition BlendDef = Definition.BlendStateDefinition;
		D3D11_BLEND_DESC BlendDesc;
		SMemory::Zero(&BlendDesc, sizeof(BlendDesc));

		BlendDesc.AlphaToCoverageEnable = true;
		BlendDesc.IndependentBlendEnable = BlendDef.EnabledIndependentBlend;


		D3D11_RENDER_TARGET_BLEND_DESC& RenderTarget = BlendDesc.RenderTarget[0];
		RenderTarget.BlendEnable = true;

		RenderTarget.SrcBlend = EngineBlendToDX11(BlendDef.RenderTarget.ColorBlendSrc);
		RenderTarget.DestBlend = EngineBlendToDX11(BlendDef.RenderTarget.ColorBlendDest);
		RenderTarget.BlendOp = EngineBlendOpToDX11(BlendDef.RenderTarget.ColorBlendOperation);

		RenderTarget.SrcBlendAlpha = EngineBlendToDX11(BlendDef.RenderTarget.AlphaBlendSrc);
		RenderTarget.DestBlendAlpha = EngineBlendToDX11(BlendDef.RenderTarget.AlphaBlendDest);
		RenderTarget.BlendOpAlpha = EngineBlendOpToDX11(BlendDef.RenderTarget.AlphaBlendOperation);

		if (BlendDef.RenderTarget.ColorWriteMask & RTWM_RED)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_RED;

		if (BlendDef.RenderTarget.ColorWriteMask & RTWM_GREEN)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_GREEN;

		if (BlendDef.RenderTarget.ColorWriteMask & RTWM_BLUE)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_BLUE;

		if (BlendDef.RenderTarget.ColorWriteMask & RTWM_ALPHA)
			RenderTarget.RenderTargetWriteMask |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
		if (FAILED(GetDXDevice()->CreateBlendState(&BlendDesc, &DXBlendState)))
		{
			LOG("Error: [DX11RHI] Failed to create a Blend state!");
			exit(-1);
		}
	}

	ID3D11RasterizerState* DXRasterizerState = NULL;
	{
		RHIRasterizerStateDefinition RasterizerDef = Definition.RasterizerStateDefinition;
		D3D11_RASTERIZER_DESC RasterizerDesc;
		SMemory::Zero(&RasterizerDesc, sizeof(RasterizerDesc));
		RasterizerDesc.CullMode = EngineCullModeToDX11(RasterizerDef.CullMode);
		RasterizerDesc.FillMode = EngineFillModeToDX11(RasterizerDef.FillMode);
		RasterizerDesc.ScissorEnable = false;
		RasterizerDesc.DepthClipEnable = true;
		RasterizerDesc.FrontCounterClockwise = true;
		RasterizerDesc.DepthBias = (INT)RasterizerDef.DepthBias;
		RasterizerDesc.MultisampleEnable = RasterizerDef.EnableMSAA;
		RasterizerDesc.SlopeScaledDepthBias = RasterizerDef.SlopeScaleDepthBias;

		if (FAILED(GetDXDevice()->CreateRasterizerState(&RasterizerDesc, &DXRasterizerState)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Rasterizer State!");
			exit(-1);
		}
	}

	ID3D11DepthStencilState* DXDepthStencilState = NULL;
	{
		RHIDepthStencilStateDefinition DepthDef = Definition.DepthStencilStateDefinition;
		D3D11_DEPTH_STENCIL_DESC DepthStecilDesc;
		SMemory::Zero(&DepthStecilDesc, sizeof(DepthStecilDesc));
		DepthStecilDesc.DepthEnable = true;

		if (DepthDef.EnabledDepthWrite)
			DepthStecilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		else
			DepthStecilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		DepthStecilDesc.DepthFunc = EngineCompareFuncToDX11(DepthDef.DepthTest);
		DepthStecilDesc.StencilEnable = DepthDef.EnabledBackFaceStencil | DepthDef.EnabledFrontFaceStencil;
		DepthStecilDesc.StencilReadMask = DepthDef.StencilReadMask;
		DepthStecilDesc.StencilWriteMask = DepthDef.StencilWriteMask;

		DepthStecilDesc.FrontFace.StencilFunc = EngineCompareFuncToDX11(DepthDef.FFStencilTest);
		DepthStecilDesc.FrontFace.StencilFailOp = EngineDSOpToDX11(DepthDef.FFStencilFailOp);
		DepthStecilDesc.FrontFace.StencilDepthFailOp = EngineDSOpToDX11(DepthDef.FFDepthFailOp);
		DepthStecilDesc.FrontFace.StencilPassOp = EngineDSOpToDX11(DepthDef.FFPassFailOp);

		if (DepthDef.EnabledBackFaceStencil)
		{
			DepthStecilDesc.BackFace.StencilFunc = EngineCompareFuncToDX11(DepthDef.BFStencilTest);
			DepthStecilDesc.BackFace.StencilFailOp = EngineDSOpToDX11(DepthDef.BFStencilFailOp);
			DepthStecilDesc.BackFace.StencilDepthFailOp = EngineDSOpToDX11(DepthDef.BFDepthFailOp);
			DepthStecilDesc.BackFace.StencilPassOp = EngineDSOpToDX11(DepthDef.BFPassFailOp);
		}
		else
			DepthStecilDesc.BackFace = DepthStecilDesc.FrontFace;

		if (FAILED(GetDXDevice()->CreateDepthStencilState(&DepthStecilDesc, &DXDepthStencilState)))
		{
			LOG("Error: [DX11RHI] Failed to create a Blend state!");
			exit(-1);
		}
	}

	return new DX11PipelineState(DXInputLayout, VertexShader->GetShader(), PixelShader->GetShader()
	, DXBlendState, DXRasterizerState, DXDepthStencilState);
}