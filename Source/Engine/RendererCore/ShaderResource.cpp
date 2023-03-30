#include <Engine/RendererCore/ShaderResource.h>

namespace GeometricEngine
{

	ShaderResource::ShaderResource()
		: VertexShader(NULL)
		, PixelShader(NULL)
		, Type(ShaderType::None)
	{

	}
	ShaderResource::ShaderResource(const ShaderCompilerOutput& Output)
	{
		Type = Output.Type;
		ShaderName = Output.ShaderName;
		if (Type == ShaderType::Pixel)
			PixelShader = GDynamicRHI->RHICreatePixelShader(Output.Code);
		else if (Type == ShaderType::Vertex)
			VertexShader = GDynamicRHI->RHICreateVertexShader(Output.Code);
	}
	ShaderResource::~ShaderResource()
	{

	}
	VertexDelaration::VertexDelaration()
		: VertexLayout(NULL)
	{
	}
	VertexDelaration::VertexDelaration(const ShaderResource* VertexShader, const TVector<BufferElement>& BufferElements)
	{
		_ASSERT(VertexShader->GetType() == ShaderType::Vertex);
		_ASSERT(VertexShader->GetVertexShader() != NULL);
		VertexLayout = GDynamicRHI->RHICreateVertexLayout(VertexShader->GetVertexShader(), BufferElements);

	}
	VertexDelaration::~VertexDelaration()
	{
	}
}