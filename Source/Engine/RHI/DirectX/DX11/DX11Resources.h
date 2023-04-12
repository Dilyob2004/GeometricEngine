#ifndef DX11RESOURCE_H
#define DX11RESOURCE_H

#include <Engine/RHI/DirectX/DX11DynamicRHI.h>

namespace GeometricEngine
{
	class DX11Texture2D : public RHITexture2D
	{
	public:

		DX11Texture2D();
		DX11Texture2D(ID3D11Texture2D*, ID3D11RenderTargetView*, ID3D11ShaderResourceView*, ID3D11DepthStencilView*, const RHITextureDefinition& );
		virtual ~DX11Texture2D();

		virtual void SafeRelease() override
		{

			if (DXTexture) DXTexture->Release(), DXTexture = NULL;
			if (DXRenderTargetView) DXRenderTargetView->Release(), DXRenderTargetView = NULL;
			if (DXShaderResourceView) DXShaderResourceView->Release(), DXShaderResourceView = NULL;
			if(DXDepthStencilView)  DXDepthStencilView->Release(), DXDepthStencilView = NULL;
		}
		ID3D11Texture2D* GetTexture() const
		{
			return DXTexture;
		}
		ID3D11ShaderResourceView* GetSRV() const
		{
			return DXShaderResourceView;
		}
		ID3D11ShaderResourceView** GetInitSRV()
		{
			return &DXShaderResourceView;
		}
		virtual void* GetHandle() override
		{
			return DXShaderResourceView;
		}
		ID3D11DepthStencilView* GetDSV() const
		{
			return DXDepthStencilView;
		}
		ID3D11RenderTargetView* GetRTV() const
		{
			return DXRenderTargetView;
		}
		ID3D11RenderTargetView** GetInitRTV()
		{
			return &DXRenderTargetView;
		}
	private:
		ID3D11Texture2D* DXTexture;
		ID3D11ShaderResourceView* DXShaderResourceView;
		ID3D11DepthStencilView* DXDepthStencilView;
		ID3D11RenderTargetView* DXRenderTargetView;
	};
	class DX11SamplerState : public RHISamplerState
	{
	public:
		DX11SamplerState();
		DX11SamplerState(ID3D11SamplerState*);
		virtual ~DX11SamplerState();

		ID3D11SamplerState* GetSamplerState() const { return DXSamplerState; }
		ID3D11SamplerState** GetInitSamplerState() { return &DXSamplerState; }
	private:
		ID3D11SamplerState* DXSamplerState;
	};
	class DX11RasterizerState : public RHIRasterizerState
	{
	public:
		DX11RasterizerState();
		DX11RasterizerState(ID3D11RasterizerState*);
		virtual ~DX11RasterizerState();

		ID3D11RasterizerState* GetRasterizerState() const { return DXRasterizerState; }
	private:
		ID3D11RasterizerState* DXRasterizerState;
	};
	class DX11BlendState : public RHIBlendState
	{
	public:
		DX11BlendState();
		DX11BlendState(ID3D11BlendState*);
		virtual ~DX11BlendState();

		ID3D11BlendState* GetBlendState() const { return DXBlendState; }
	private:
		ID3D11BlendState* DXBlendState;
	};
	class DX11DepthStencilState : public RHIDepthStencilState
	{
	public:
		DX11DepthStencilState();
		DX11DepthStencilState(ID3D11DepthStencilState*);
		virtual ~DX11DepthStencilState();

		ID3D11DepthStencilState* GetDepthStencilState() const { return DXDepthStencilState; }
	private:
		ID3D11DepthStencilState* DXDepthStencilState;
	};
}
#endif // !DX11RESOURCE_H
