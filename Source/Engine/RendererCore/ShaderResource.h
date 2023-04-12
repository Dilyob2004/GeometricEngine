#ifndef SHADERRESOURCE_H
#define SHADERRESOURCE_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/ShaderCompiler/ShaderCompiler.h>
#include <Engine/Core/Misc/References.h> 
namespace GeometricEngine
{
	class GEOMETRIC_API BoundShaderResource
	{
	public:
		BoundShaderResource();
		BoundShaderResource(
			const TVector<BufferElement>& BufferElement,
			RHIVertexShader* VertexShader,
			RHIPixelShader* PixelShader);
		~BoundShaderResource();

		void OnTick();

		RHIVertexLayout* GetVertexLayout() const { return VertexLayout; }
		RHIVertexShader* GetVertexShader() const { return VertexShader; }
		RHIPixelShader* GetPixelShader() const { return PixelShader; }
	private:
		RHIVertexLayout* VertexLayout;
		RHIVertexShader* VertexShader;
		RHIPixelShader* PixelShader;
	};
}
#endif // !SHADERRESOURCE_H
