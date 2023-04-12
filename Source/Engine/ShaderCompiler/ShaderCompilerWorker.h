#ifndef SHADERCOMPILERWORKER_H
#define SHADERCOMPILERWORKER_H
#include <Engine/ShaderCompiler/ShaderCompiler.h>
#include <Engine/Core/Containers/Map.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/String.h>
#include <map>
namespace GeometricEngine
{
	class GEOMETRIC_API ShaderCompilerWorker
	{
	public:
		static void Initialize();
	private:
		static void AddCompile(const String& Name, ShaderType);
	};
	extern std::map < String, RHIVertexShader* > GVSResourceMap;
	extern std::map < String, RHIPixelShader* > GPSResourceMap;
	extern std::map<String, ShaderCompilerOutput> GShadersMap;
}
#endif // !SHADERCOMPILERWORKER_H
