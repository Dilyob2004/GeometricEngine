#ifndef SHADERCOMPILERWORKER_H
#define SHADERCOMPILERWORKER_H
#include <Engine/ShaderCompiler/ShaderCompiler.h>
#include <Engine/Core/Containers/Map.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/String.h>
#include <map>

class GEOMETRIC_API ShaderCompileWorker
{
public:
	static void DefaultInitialize();
private:
	static void AddCompile(const String& Name, ShaderType);
};
extern std::map < String, RHIVertexShader* > GVertexShaderMap;
extern std::map < String, RHIPixelShader* > GPixelShaderMap;

#endif // !SHADERCOMPILERWORKER_H
