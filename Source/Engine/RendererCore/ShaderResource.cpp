#include <Engine/RendererCore/ShaderResource.h>

namespace GeometricEngine
{

	BoundShaderResource::BoundShaderResource()
	{

	}
	BoundShaderResource::BoundShaderResource( const TVector<BufferElement>& ElementList,
											  RHIVertexShader* VS,
											  RHIPixelShader*  PS)
		: VertexShader(VS)
		, PixelShader(PS)
	{
		VertexLayout = GDynamicRHI->RHICreateVertexLayout(VS, ElementList);
	}
	BoundShaderResource::~BoundShaderResource()
	{
	}

	void BoundShaderResource::OnTick()
	{
		GDynamicRHI->RHISetVertexLayout(VertexLayout);
		GDynamicRHI->RHISetPixelShader(PixelShader);
		GDynamicRHI->RHISetVertexShader(VertexShader);
	}

}