
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>

void DX11DynamicRHI::RHISetPipelineState(RHIPipelineState* PipelineStateRHI)
{
	DYNAMIC_CAST(DX11PipelineState, PipelineState, PipelineStateRHI);


	DXDeviceContext->IASetInputLayout(PipelineState->GetDXInputLayout());
	DXDeviceContext->PSSetShader(PipelineState->GetDXPixelShader(), 0, 0);
	DXDeviceContext->VSSetShader(PipelineState->GetDXVertexShader(), 0, 0);

	DXDeviceContext->RSSetState(PipelineState->GetDXRasterizerState());
	DXDeviceContext->OMSetBlendState(PipelineState->GetDXBlendState(), BlendFactor, 0xFFFFFFFF);
	DXDeviceContext->OMSetDepthStencilState(PipelineState->GetDXDepthStencilState(), 0);

}
void DX11DynamicRHI::RHIClearRenderTarget(RHIRenderTarget* TargetRHI, F32 r, F32 g, F32 b, F32 a)
{
	F32 Colos[] = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
	DYNAMIC_CAST(DX11RenderTarget, Target, TargetRHI);
	DXDeviceContext->ClearRenderTargetView(Target->GetRTV(), Colos);
}

void DX11DynamicRHI::RHIClearDepthTarget(RHIDepthTarget* TargetRHI, bool UseDepth, bool UseStencil, F32 Depth)
{
	DYNAMIC_CAST(DX11DepthTarget, Target, TargetRHI);
	if (UseDepth)   DepthFlag |= D3D11_CLEAR_DEPTH;
	if (UseStencil) DepthFlag |= D3D11_CLEAR_STENCIL;
	DXDeviceContext->ClearDepthStencilView(Target->GetDSV(), DepthFlag, Depth, 0xFF);
}
void DX11DynamicRHI::RHISetRenderTarget(RHIRenderTarget* RenderTarget)
{
	if(RenderTarget)
	{
		DYNAMIC_CAST(DX11RenderTarget, View, RenderTarget);
		DXDeviceContext->OMSetRenderTargets(1, View->GetInitRTV(), NULL);
		RHISetViewport(0, 0, (F32)View->GetWidth(), (F32)View->GetHeight());
	}
	else
		DXDeviceContext->OMSetRenderTargets(0, NULL, NULL);
}
void DX11DynamicRHI::RHICopyRenderTarget(RHIRenderTarget* SourceTextureRHI, RHIRenderTarget* DestTextureRHI)
{
	DYNAMIC_CAST(DX11RenderTarget, SourceTexture, SourceTextureRHI);
	DYNAMIC_CAST(DX11RenderTarget, DestTexture, DestTextureRHI);
	DXDeviceContext->CopyResource(DestTexture->GetTexture(), SourceTexture->GetTexture());
}

void DX11DynamicRHI::RHIResizeRenderTarget(RHIRenderTarget** RenderTargetRHI, U32 Width, U32 Height)
{
	(*RenderTargetRHI)->SafeRelease();
	RHITextureDefinition Definition;
	Definition.Width = Width;
	Definition.Height = Height;
	Definition.Format = (*RenderTargetRHI)->GetFormat();
	Definition.Samples = (*RenderTargetRHI)->GetNumSamples();
	Definition.MipLevels = (*RenderTargetRHI)->GetNumMipmaps();
	(*RenderTargetRHI) = RHICreateRenderTarget(Definition);
}
void DX11DynamicRHI::RHISetRenderTarget(RHIRenderTarget* RenderTarget, RHIDepthTarget* DepthTarget)
{
	DYNAMIC_CAST(DX11RenderTarget, View, RenderTarget);
	DYNAMIC_CAST(DX11DepthTarget, Depth, DepthTarget);

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
void DX11DynamicRHI::RHISetPixelShaderSampler(RHISamplerState* SamplerStateRHI)
{
	DYNAMIC_CAST(DX11SamplerState, Sampler, SamplerStateRHI);
	DXDeviceContext->PSSetSamplers(0, 1, Sampler->GetInitSamplerState());
}
void DX11DynamicRHI::RHISetVertexShaderSampler(RHISamplerState* SamplerStateRHI)
{
	DYNAMIC_CAST(DX11SamplerState, Sampler, SamplerStateRHI);
	DXDeviceContext->VSSetSamplers(0, 1, Sampler->GetInitSamplerState());
}
void DX11DynamicRHI::RHISetPixelShaderTexture(RHITexture2D* TextureRHI)
{
	DYNAMIC_CAST(DX11Texture2D, Texture, TextureRHI);
	DXDeviceContext->PSSetShaderResources(0, 1, Texture->GetInitSRV());
}
void DX11DynamicRHI::RHISetVertexShaderTexture(RHITexture2D* TextureRHI)
{
	DYNAMIC_CAST(DX11Texture2D, Texture, TextureRHI);
	DXDeviceContext->VSSetShaderResources(0, 1, Texture->GetInitSRV());
}

void DX11DynamicRHI::RHISetPixelShaderUniformBuffer(RHIUniformBuffer* UniformBufferRHI)
{
	DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
	DXDeviceContext->PSSetConstantBuffers(0, 1, UniformBuffer->GetInitUniformBuffer());
}

void DX11DynamicRHI::RHISetVertexShaderUniformBuffer(RHIUniformBuffer* UniformBufferRHI)
{
	DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
	DXDeviceContext->VSSetConstantBuffers(0, 1, UniformBuffer->GetInitUniformBuffer());
}
	
	
void DX11DynamicRHI::RHIUpdateUniformBuffer(RHIUniformBuffer* UniformBufferRHI, const void* Data, U32 Size)
{
	DYNAMIC_CAST(DX11UniformBuffer, UniformBuffer, UniformBufferRHI);
	D3D11_BUFFER_DESC Desc;
	UniformBuffer->GetUniformBuffer()->GetDesc(&Desc);
	if (Desc.Usage == D3D11_USAGE_DYNAMIC)
	{

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DXDeviceContext->Map(UniformBuffer->GetUniformBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, Data, Size);
		DXDeviceContext->Unmap(UniformBuffer->GetUniformBuffer(), 0);
	}
	else	
		DXDeviceContext->UpdateSubresource(UniformBuffer->GetUniformBuffer(), 0, NULL, Data, Size, 0);


}

void DX11DynamicRHI::RHIUpdateVertexBuffer(RHIVertexBuffer* VertexBufferRHI, const void* Data, U32 Size)
{
	DYNAMIC_CAST(DX11VertexBuffer, VertexBuffer, VertexBufferRHI);
	D3D11_BUFFER_DESC Desc;
	VertexBuffer->GetVertexBuffer()->GetDesc(&Desc);
	if (Desc.Usage == D3D11_USAGE_DYNAMIC)
	{

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DXDeviceContext->Map(VertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, Data, Size);
		DXDeviceContext->Unmap(VertexBuffer->GetVertexBuffer(), 0);
	}
	else
		DXDeviceContext->UpdateSubresource(VertexBuffer->GetVertexBuffer(), 0, NULL, Data, Size, 0);
}
void DX11DynamicRHI::RHIUpdateIndexBuffer(RHIIndexBuffer* IndexBufferRHI, const void* Data, U32 Size)
{
	DYNAMIC_CAST(DX11IndexBuffer, IndexBuffer, IndexBufferRHI);
	D3D11_BUFFER_DESC Desc;
	IndexBuffer->GetIndexBuffer()->GetDesc(&Desc);
	if (Desc.Usage == D3D11_USAGE_DYNAMIC)
	{

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DXDeviceContext->Map(IndexBuffer->GetIndexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, Data, Size);
		DXDeviceContext->Unmap(IndexBuffer->GetIndexBuffer(), 0);
	}
	else
		DXDeviceContext->UpdateSubresource(IndexBuffer->GetIndexBuffer(), 0, NULL, Data, Size, 0);


}
void DX11DynamicRHI::RHIDrawPrimitiveIndexed(RHIVertexBuffer* VertexBufferRHI, RHIIndexBuffer* IndexBufferRHI, U32 Count, U32 Start, DrawType type)
{
	DYNAMIC_CAST(DX11IndexBuffer, IndexBuffer, IndexBufferRHI);
	DYNAMIC_CAST(DX11VertexBuffer, VertexBuffer, VertexBufferRHI);

	U32 Stride = VertexBuffer->GetStride();
	U32 Offset = VertexBuffer->GetOffset();

	DXDeviceContext->IASetVertexBuffers(0, 1, VertexBuffer->GetInitVertexBuffer(), &Stride, &Offset);
	DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
	DXDeviceContext->IASetIndexBuffer(IndexBuffer->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	DXDeviceContext->DrawIndexed(Count, Start, 0);
}
void DX11DynamicRHI::RHIDrawPrimitive(RHIVertexBuffer* VertexBufferRHI, U32 Count, U32 Start, DrawType type)
{
	DYNAMIC_CAST(DX11VertexBuffer, VertexBuffer, VertexBufferRHI);
	U32 Stride = VertexBuffer->GetStride();
	U32 Offset = VertexBuffer->GetOffset();

	DXDeviceContext->IASetVertexBuffers(0, 1, VertexBuffer->GetInitVertexBuffer(), &Stride, &Offset);
	DXDeviceContext->IASetPrimitiveTopology(DrawTypeEngineToDX11(type));
	DXDeviceContext->Draw(Count, Start);
}

