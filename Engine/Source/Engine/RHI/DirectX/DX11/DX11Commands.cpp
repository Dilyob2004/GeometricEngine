
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>



namespace GeometricEngine
{

	void DX11DynamicRHI::RHIClearRenderTarget(RHITexture2D* TargetRHI, F32 r, F32 g, F32 b, F32 a)
	{
		F32 Colos[] = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
		DYNAMIC_CAST(DX11Texture2D, Target, TargetRHI);
		DXDeviceContext->ClearRenderTargetView(Target->GetRTV(), Colos);
	}

	void DX11DynamicRHI::RHIClearDepthTarget(RHITexture2D* TargetRHI, bool UseDepth, bool UseStencil, F32 Depth)
	{
		DYNAMIC_CAST(DX11Texture2D, Target, TargetRHI);
		if (UseDepth)   DepthFlag |= D3D11_CLEAR_DEPTH;
		if (UseStencil) DepthFlag |= D3D11_CLEAR_STENCIL;
		DXDeviceContext->ClearDepthStencilView(Target->GetDSV(), DepthFlag, Depth, 0xFF);
	}
	void DX11DynamicRHI::RHISetRenderTarget(RHITexture2D* RenderTarget)
	{
		if(RenderTarget != NULL)
		{
			DYNAMIC_CAST(DX11Texture2D, View, RenderTarget);
			DXDeviceContext->OMSetRenderTargets(1, View->GetInitRTV(), NULL);
			RHISetViewport(0, 0, (F32)View->GetWidth(), (F32)View->GetHeight());
		}
		else
			DXDeviceContext->OMSetRenderTargets(0, NULL, NULL);
	}
	void DX11DynamicRHI::RHICopyRenderTarget(RHITexture2D* SourceTextureRHI, RHITexture2D* DestTextureRHI)
	{
		DYNAMIC_CAST(DX11Texture2D, SourceTexture, SourceTextureRHI);
		DYNAMIC_CAST(DX11Texture2D, DestTexture, DestTextureRHI);
		DXDeviceContext->CopyResource(DestTexture->GetTexture(), SourceTexture->GetTexture());
	}
	void DX11DynamicRHI::RHISetRenderTarget(RHITexture2D* RenderTarget, RHITexture2D* DepthTarget)
	{
		DYNAMIC_CAST(DX11Texture2D, View, RenderTarget);
		DYNAMIC_CAST(DX11Texture2D, Depth, DepthTarget);

		DXDeviceContext->OMSetRenderTargets(1, View->GetInitRTV(), Depth->GetDSV());

		RHISetViewport(0, 0, (F32)View->GetWidth(), (F32)View->GetHeight());
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

	void DX11DynamicRHI::RHISetUniformBuffer(const RHIVertexShader* ShaderRHI, const RHIUniformBuffer* UniformBufferRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
		DXDeviceContext->VSSetConstantBuffers(0, 1, UniformBuffer->GetInitUniformBuffer());
	}

	void DX11DynamicRHI::RHISetUniformBuffer(const RHIPixelShader* ShaderRHI, const RHIUniformBuffer* UniformBufferRHI)
	{
		_ASSERT(ShaderRHI != NULL);
		DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
		DXDeviceContext->PSSetConstantBuffers(0, 1, UniformBuffer->GetInitUniformBuffer());
	}

	void DX11DynamicRHI::RHISetVertexBuffer(const RHIVertexBuffer* VertexBufferRHI)
	{
		DYNAMIC_CAST(DX11VertexBuffer, VertexBuffer, VertexBufferRHI);
		U32 Stride = VertexBuffer->GetBufferView().Stride;
		U32 Offset = VertexBuffer->GetBufferView().Offset;
		DXDeviceContext->IASetVertexBuffers(0, 1, VertexBuffer->GetInitVertexBuffer(), &Stride, &Offset);
	}

	
	
	void DX11DynamicRHI::RHIUpdateUniformBuffer(const RHIUniformBuffer* UniformBufferRHI, void* Data, U32 Size)
	{
		DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
		DXDeviceContext->UpdateSubresource(UniformBuffer->GetUniformBuffer(), 0, NULL, Data, Size, 0);
	}
	void DX11DynamicRHI::RHIDrawPrimitiveIndexed(RHIIndexBuffer* IndexBufferRHI, U32 Count, U32 Start, DrawType type)
	{
		DYNAMIC_CAST(DX11IndexBuffer, IndexBuffer, IndexBufferRHI);
		DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
		DXDeviceContext->IASetIndexBuffer(IndexBuffer->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
		DXDeviceContext->DrawIndexed(Count, Start, 0);
	}
	void DX11DynamicRHI::RHIDrawPrimitive(U32 Count, U32 Start, DrawType type)
	{
		DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
		DXDeviceContext->Draw(Count, Start);
	}

}