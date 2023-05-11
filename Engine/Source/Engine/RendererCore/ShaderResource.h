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
		~BoundShaderResource();

		void OnTick();

		RHIVertexShader* GetVertexShader() const { return VertexShader; }
		RHIPixelShader* GetPixelShader() const { return PixelShader; }
	private:
		RHIVertexShader* VertexShader;
		RHIPixelShader* PixelShader;
	};
}
#endif // !SHADERRESOURCE_H
