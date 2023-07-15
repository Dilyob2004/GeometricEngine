#ifndef DX11RESOURCE_H
#define DX11RESOURCE_H

#include <Engine/RHI/DirectX/DX11DynamicRHI.h>

class DX11Texture2D : public RHITexture2D
{
public:

	DX11Texture2D()
		: RHITexture2D()
		, DXTexture(NULL)
		, DXShaderResourceView(NULL)
	{
	}
	DX11Texture2D(ID3D11Texture2D* D3DTexture, ID3D11ShaderResourceView* D3DSRV, const RHITextureDefinition& Definitions)
		: RHITexture2D(Definitions.Width, Definitions.Height, Definitions.MipLevels, Definitions.Samples, Definitions.Format)
		, DXTexture(D3DTexture)
		, DXShaderResourceView(D3DSRV)
	{
	}
	virtual ~DX11Texture2D()
	{
		SafeRelease();
	}

	virtual void SafeRelease() override
	{
		if (DXTexture) DXTexture->Release(), DXTexture = NULL;
		if (DXShaderResourceView) DXShaderResourceView->Release(), DXShaderResourceView = NULL;
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
private:
	ID3D11Texture2D* DXTexture;
	ID3D11ShaderResourceView* DXShaderResourceView;
};
class DX11RenderTarget : public RHIRenderTarget
{
public:

	DX11RenderTarget()
		: RHIRenderTarget()
		, DXTexture(NULL)
		, DXShaderResourceView(NULL)
		, DXRenderTargetView(NULL)
	{
	}
	DX11RenderTarget(ID3D11Texture2D* D3DTexture,
		ID3D11RenderTargetView* D3DRTV,
		ID3D11ShaderResourceView* D3DSRV,
		const RHITextureDefinition& Definitions)
		: RHIRenderTarget(Definitions.Width, Definitions.Height, Definitions.MipLevels, Definitions.Samples, Definitions.Format)
		, DXTexture(D3DTexture)
		, DXShaderResourceView(D3DSRV)
		, DXRenderTargetView(D3DRTV)
	{
	}
	virtual ~DX11RenderTarget()
	{
		SafeRelease();
	}

	virtual void SafeRelease() override
	{

		if (DXTexture) DXTexture->Release(), DXTexture = NULL;
		if (DXRenderTargetView) DXRenderTargetView->Release(), DXRenderTargetView = NULL;
		if (DXShaderResourceView) DXShaderResourceView->Release(), DXShaderResourceView = NULL;
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
	ID3D11RenderTargetView* DXRenderTargetView;
};

class DX11DepthTarget: public RHIDepthTarget
{
public:

	DX11DepthTarget()
		: RHIDepthTarget()
		, DXTexture(NULL)
		, DXDepthStencilView(NULL)
		, DXShaderResourceView(NULL)
	{
	}
	DX11DepthTarget(ID3D11Texture2D* D3DTexture, ID3D11ShaderResourceView* D3DSRV, ID3D11DepthStencilView* D3DDSV, const RHITextureDefinition& Definitions)

		: RHIDepthTarget(Definitions.Width, Definitions.Height, Definitions.MipLevels, Definitions.Samples, Definitions.Format)
		, DXTexture(D3DTexture)
		, DXShaderResourceView(D3DSRV)
		, DXDepthStencilView(D3DDSV)
	{
	}

	virtual ~DX11DepthTarget()
	{
		SafeRelease();
	}

	virtual void SafeRelease() override
	{
		if (DXTexture) DXTexture->Release(), DXTexture = NULL;
		if (DXShaderResourceView) DXShaderResourceView->Release(), DXShaderResourceView = NULL;
		if (DXDepthStencilView)  DXDepthStencilView->Release(), DXDepthStencilView = NULL;
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
private:
	ID3D11Texture2D* DXTexture;
	ID3D11ShaderResourceView* DXShaderResourceView;
	ID3D11DepthStencilView* DXDepthStencilView;
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

class DX11PipelineState : public RHIPipelineState
{
public:
	DX11PipelineState()
		: DXInputLayout(NULL),
		DXVertexShader(NULL),
		DXPixelShader(NULL),
		DXBlendState(NULL),
		DXRasterizerState(NULL),
		DXDepthStencilState(NULL)
	{
	}
	DX11PipelineState(
		ID3D11InputLayout* DX11InputLayout,
		ID3D11VertexShader* DX11VertexShader,
		ID3D11PixelShader* DX11PixelShader,
		ID3D11BlendState* DX11BlendState,
		ID3D11RasterizerState* DX11RasterizerState,
		ID3D11DepthStencilState* DX11DepthStencilState) 
		:	DXInputLayout(DX11InputLayout),
			DXVertexShader(DX11VertexShader),
			DXPixelShader(DX11PixelShader),
			DXBlendState(DX11BlendState),
			DXRasterizerState(DX11RasterizerState),
			DXDepthStencilState(DX11DepthStencilState)
	{
	}
	virtual ~DX11PipelineState()
	{
		if (DXInputLayout)			DXInputLayout->Release();
		if (DXVertexShader)			DXVertexShader->Release();
		if (DXPixelShader)			DXPixelShader->Release();
		if (DXBlendState)			DXBlendState->Release();
		if (DXRasterizerState)		DXRasterizerState->Release();
		if (DXDepthStencilState)	DXDepthStencilState->Release();
	}
	ID3D11InputLayout* GetDXInputLayout() const { return DXInputLayout; }
	ID3D11VertexShader* GetDXVertexShader() const{ return DXVertexShader; }
	ID3D11PixelShader* GetDXPixelShader() const{ return DXPixelShader; }
	ID3D11BlendState* GetDXBlendState() const{ return DXBlendState; }
	ID3D11RasterizerState* GetDXRasterizerState() const{ return DXRasterizerState; }
	ID3D11DepthStencilState* GetDXDepthStencilState() const{ return DXDepthStencilState; }
private:
	ID3D11InputLayout* DXInputLayout;
	ID3D11VertexShader* DXVertexShader;
	ID3D11PixelShader* DXPixelShader;
	ID3D11BlendState* DXBlendState;
	ID3D11RasterizerState* DXRasterizerState;
	ID3D11DepthStencilState* DXDepthStencilState;
};
#endif // !DX11RESOURCE_H
