#ifndef SHADERRESOURCE_H
#define SHADERRESOURCE_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/ShaderCompiler/ShaderCompiler.h>

namespace GeometricEngine
{
	class GEOMETRIC_API ShaderResource
	{
	public:
		ShaderResource();
		ShaderResource(const ShaderCompilerOutput&);
		~ShaderResource();

		ShaderType GetType() const { return Type; }
		RHIVertexShader* GetVertexShader() const
		{
			_ASSERT(Type == ShaderType::Vertex);
			return VertexShader;
		}
		RHIPixelShader* GetPixelShader() const
		{
			_ASSERT(Type == ShaderType::Pixel);
			return PixelShader;
		}
	private:
		ShaderType Type;
		String ShaderName;
		RHIVertexShader* VertexShader;
		RHIPixelShader* PixelShader;
	};
	class GEOMETRIC_API VertexDelaration
	{
	public:
		VertexDelaration();
		VertexDelaration(const ShaderResource*, const TVector<BufferElement>& );
		~VertexDelaration();

		RHIVertexLayout* GetVertexLayout() const { return VertexLayout; }
	private:
		RHIVertexLayout* VertexLayout;
	};
}
#endif // !SHADERRESOURCE_H
