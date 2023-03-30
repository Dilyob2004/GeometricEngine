
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>



namespace GeometricEngine
{

	void DX11DynamicRHI::RHIClearViewport(const RHIViewport* ViewportRHI, F32 r, F32 g, F32 b, F32 a)
	{
		F32 Colos[] = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };

		DYNAMIC_CAST(DX11Viewport, Viewport, ViewportRHI);
		DYNAMIC_CAST(DX11Texture2D, View, Viewport->GetBackBufferView());

		DXDeviceContext->ClearRenderTargetView(View->GetRTV(), Colos);
	}
	void DX11DynamicRHI::RHISetRenderTarget(const RHITexture* RenderTarget)
	{
		DYNAMIC_CAST(DX11Texture2D, View, RenderTarget);
		DXDeviceContext->OMSetRenderTargets(1, View->GetInitRTV(), NULL);
	}
	void DX11DynamicRHI::RHISetRenderTarget(const RHITexture* RenderTarget, const RHITexture* DepthTarget)
	{
		DYNAMIC_CAST(DX11Texture2D, View, RenderTarget);
		DYNAMIC_CAST(DX11Texture2D, Depth, DepthTarget);
		DXDeviceContext->OMSetRenderTargets(1, View->GetInitRTV(), Depth->GetDSV());
	}
	void DX11DynamicRHI::RHISetScissorRect(U32 MinX, U32 MaxX, U32 MinY, U32 MaxY)
	{
		D3D11_RECT Rect;
		SMemory::Zero(&Rect, sizeof(Rect));
		Rect.left		= MinX;
		Rect.right		= MaxX;
		Rect.top		= MinY;
		Rect.bottom		= MaxY;
		DXDeviceContext->RSSetScissorRects(1, &Rect);
	}
	void DX11DynamicRHI::RHISetViewport(F32 MinX, F32 MinY, F32 MaxX, F32 MaxY)
	{
		D3D11_VIEWPORT Viewport;
		SMemory::Zero(&Viewport, sizeof(Viewport));
		Viewport.TopLeftX	= MinX;
		Viewport.TopLeftY	= MinY;
		Viewport.Width		= MaxX;
		Viewport.Height		= MaxY;
		Viewport.MinDepth	= 0;
		Viewport.MaxDepth	= 1;
		DXDeviceContext->RSSetViewports(1, &Viewport);
	}

	void DX11DynamicRHI::RHISetPixelShader(const RHIPixelShader* PixelShaderRHI)
	{
		DYNAMIC_CAST(DX11PixelShader, PixelShader, PixelShaderRHI);
		DXDeviceContext->PSSetShader(PixelShader->GetShader(), 0, 0);
	}

	void DX11DynamicRHI::RHISetVertexShader(const RHIVertexShader* VertexShaderRHI)
	{
		DYNAMIC_CAST(DX11VertexShader, VertexShader, VertexShaderRHI);
		DXDeviceContext->VSSetShader(VertexShader->GetShader(), 0, 0);
	}

	void DX11DynamicRHI::RHISetVertexLayout(const RHIVertexLayout* VertexLayoutRHI)
	{
		DYNAMIC_CAST(DX11VertexLayout, VertexLayout, VertexLayoutRHI);
		DXDeviceContext->IASetInputLayout(VertexLayout->GetInputLayout());
	}

	void DX11DynamicRHI::RHISetRasterizerState(const RHIRasterizerState* RasterizerStateRHI)
	{
		DYNAMIC_CAST(DX11RasterizerState, State, RasterizerStateRHI);
		DXDeviceContext->RSSetState(State->GetRasterizerState());
	}
	void DX11DynamicRHI::RHISetBlendState(const RHIBlendState* BlendStateRHI)
	{
		DYNAMIC_CAST(DX11BlendState, State, BlendStateRHI);
		float BlendFactor[4] = { 0, 0, 0, 0 };
		DXDeviceContext->OMSetBlendState(State->GetBlendState(), BlendFactor, 0xFFFFFFFF);
	}

	void DX11DynamicRHI::RHISetDepthStencilState(const RHIDepthStencilState* DepthStencilRHI)
	{
		DYNAMIC_CAST(DX11DepthStencilState, State, DepthStencilRHI);
		DXDeviceContext->OMSetDepthStencilState(State->GetDepthStencilState(), 0);
	}
	void DX11DynamicRHI::RHISetSamplerState(const RHIPixelShader* ShaderRHI, const RHISamplerState* SamplerStateRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11SamplerState, Sampler, SamplerStateRHI);
		DXDeviceContext->PSSetSamplers(0, 1, Sampler->GetInitSamplerState());
	}
	void DX11DynamicRHI::RHISetTexture(const RHIPixelShader* ShaderRHI, const RHITexture2D* TextureRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11Texture2D, Texture, TextureRHI);
		DXDeviceContext->PSSetShaderResources(0, 1, Texture->GetInitSRV());
	}

	void DX11DynamicRHI::RHISetConstantBuffer(const RHIVertexShader* ShaderRHI, const RHIConstantBuffer* ConstantBufferRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11ConstantBuffer, ConstantBuffer, ConstantBufferRHI);
		DXDeviceContext->VSSetConstantBuffers(0, 1, ConstantBuffer->GetInitConstantBuffer());
	}

	void DX11DynamicRHI::RHISetConstantBuffer(const RHIPixelShader* ShaderRHI, const RHIConstantBuffer* ConstantBufferRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11ConstantBuffer, ConstantBuffer, ConstantBufferRHI);
		DXDeviceContext->PSSetConstantBuffers(0, 1, ConstantBuffer->GetInitConstantBuffer());
	}

	void DX11DynamicRHI::RHISetVertexBuffer(const RHIVertexBuffer* VertexBufferRHI, const RHIVertexLayout* VertexDeclarationRHI, U32 Offset)
	{
		DYNAMIC_CAST(DX11VertexBuffer, VertexBuffer, VertexBufferRHI);
		DYNAMIC_CAST(DX11VertexLayout, VertexDeclaration, VertexDeclarationRHI);
		U32 Stride = VertexDeclaration->GetStrideLayout();
		DXDeviceContext->IASetVertexBuffers(0, 1, VertexBuffer->GetInitVertexBuffer(), &Stride, &Offset);
	}
	
	void DX11DynamicRHI::RHISetIndexBuffer(const RHIIndexBuffer* IndexBufferRHI)
	{
		DYNAMIC_CAST(DX11IndexBuffer, IndexBuffer, IndexBufferRHI);
		DXDeviceContext->IASetIndexBuffer(IndexBuffer->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11DynamicRHI::RHIUpdateConstantBuffer(const RHIConstantBuffer* ConstantBufferRHI, void* Data, U32 Size)
	{
		DYNAMIC_CAST(DX11ConstantBuffer, ConstantBuffer, ConstantBufferRHI);
		DXDeviceContext->UpdateSubresource(ConstantBuffer->GetConstantBuffer(), 0, NULL, Data, Size, 0);
	}
	void DX11DynamicRHI::RHIDrawPrimitiveIndexed(U32 Count, U32 Start, DrawType type)
	{
		DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
		DXDeviceContext->DrawIndexed(Count, Start, 0);
	}
	void DX11DynamicRHI::RHIDrawPrimitive(U32 Count, U32 Start, DrawType type)
	{
		DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
		DXDeviceContext->Draw(Count, Start);
	}

}