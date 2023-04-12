
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/Core/Misc/Log.h>


namespace GeometricEngine
{


	DX11Texture2D::DX11Texture2D()
		: RHITexture2D()
		, DXTexture(NULL)
		, DXShaderResourceView(NULL)
		, DXRenderTargetView(NULL)
		, DXDepthStencilView(NULL)
	{
	}
	DX11Texture2D::DX11Texture2D(	ID3D11Texture2D* D3DTexture, 
									ID3D11RenderTargetView* D3DRTV, 
									ID3D11ShaderResourceView* D3DSRV, 
									ID3D11DepthStencilView* D3DDSV , const RHITextureDefinition& Definitions)
		: RHITexture2D(Definitions.Width, Definitions.Height, Definitions.MipLevels, Definitions.Samples, Definitions.Format, Definitions.Flags)
		, DXTexture(D3DTexture)
		, DXShaderResourceView(D3DSRV)
		, DXRenderTargetView(D3DRTV)
		, DXDepthStencilView(D3DDSV)
	{
	}
	DX11Texture2D::~DX11Texture2D()
	{
		DXRenderTargetView->Release();
		DXShaderResourceView->Release();
		DXDepthStencilView->Release();
	}
	RHITexture2D* DX11DynamicRHI::RHICreateTexture2D(const RHITextureDefinition& Definition)
	{
		D3D11_TEXTURE2D_DESC Descriptor;
		SMemory::Zero(&Descriptor, sizeof(Descriptor));
		Descriptor.Width = Definition.Width;
		Descriptor.Height = Definition.Height;
		Descriptor.Format = RHIFormatToDX11Format(Definition.Format);
		Descriptor.MipLevels = Definition.MipLevels;
		Descriptor.SampleDesc.Count = Definition.Samples;
		Descriptor.SampleDesc.Quality =  (Definition.Samples > 1) ? D3D11_STANDARD_MULTISAMPLE_PATTERN : 0;
		Descriptor.Usage = EngineTextureUsageToDX11(Definition.Usage);
		Descriptor.ArraySize = 1;
		if (Definition.Flags & TF_ShaderResource)
			Descriptor.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		if (Definition.Flags & TF_RenderTarget)
			Descriptor.BindFlags |= D3D11_BIND_RENDER_TARGET;

		if (Definition.Flags & TF_DepthStencil)
			Descriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;


		ID3D11Texture2D* DXTexture;
		if (Definition.Data != NULL) 
		{
			D3D11_SUBRESOURCE_DATA TextureData;
			SMemory::Zero(&TextureData, sizeof(TextureData));
			TextureData.pSysMem = Definition.Data;
			TextureData.SysMemPitch = Definition.Width * 4;
			if (FAILED(GetDXDevice()->CreateTexture2D(&Descriptor, &TextureData, &DXTexture)))
			{
				LOG("Error: [DX11RHI] Failed to create a resource pSysMem texture 2D!");
				exit(-1);
			}
		}
		else
		{

			if (FAILED(GetDXDevice()->CreateTexture2D(&Descriptor, NULL, &DXTexture)))
			{
				LOG("Error: [DX11RHI] Failed to create a texture 2D!");
				exit(-1);
			}
		}
		ID3D11ShaderResourceView*	DXShaderResourceView = NULL;
		ID3D11DepthStencilView*		DXDepthStencilView = NULL;
		ID3D11RenderTargetView*		DXRenderTargetView = NULL;


		if (Definition.Flags & TF_RenderTarget)
		{
			D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
			SMemory::Zero(&RTVDesc, sizeof(RTVDesc));
			if (Descriptor.SampleDesc.Count > 1)
				RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			else
			{
				RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				RTVDesc.Texture2D.MipSlice = 0;
			}
			RTVDesc.Format = RHIFormatToDX11Format(Definition.Format);

			if (FAILED(GetDXDevice()->CreateRenderTargetView(DXTexture, &RTVDesc, &DXRenderTargetView)))
			{
				LOG("Error: [DX11RHI] Failed to create a RenderTargetView111!");
				exit(-1);
			}
		}

		if (Definition.Flags & TF_ShaderResource) 
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
			SMemory::Zero(&SRVDesc, sizeof(SRVDesc));
			if (Descriptor.SampleDesc.Count > 1)
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
			else
			{
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				SRVDesc.Texture2D.MostDetailedMip = 0;
				SRVDesc.Texture2D.MipLevels = Definition.MipLevels;
			}
			SRVDesc.Format = RHIFormatToDX11Format(Definition.Format);

			if (FAILED(GetDXDevice()->CreateShaderResourceView(DXTexture, &SRVDesc, &DXShaderResourceView)))
			{
				LOG("Error: [DX11RHI] Failed to create a shader resource view!");
				exit(-1);
			}
		}
		if (Definition.Flags & TF_DepthStencil)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
			SMemory::Zero(&DSVDesc, sizeof(DSVDesc));
			if (Descriptor.SampleDesc.Count > 1)
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			else
			{
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				DSVDesc.Texture2D.MipSlice = 0;
			}
			DSVDesc.Format = RHIFormatToDX11Format(Definition.Format);

			if (FAILED(GetDXDevice()->CreateDepthStencilView(DXTexture, &DSVDesc, &DXDepthStencilView)))
			{
				LOG("Error: [DX11RHI] Failed to create a DepthStencilView!");
				exit(-1);
			}
		}
		return new DX11Texture2D(DXTexture, DXRenderTargetView, DXShaderResourceView, DXDepthStencilView, Definition);
	}


}