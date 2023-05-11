#include "ShaderCompilerWorker.h"
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Generic/ScopeLock.h>
namespace GeometricEngine
{
	CriticalSection CompileWork;
	std::map<String, ShaderCompilerOutput> GShadersMap;
	std::map < String, RHIVertexShader* > GVSResourceMap;
	std::map < String, RHIPixelShader* > GPSResourceMap;
	void ShaderCompilerWorker::Initialize()
	{

		ScopeLock Locker(&CompileWork);
		LOG("\nState Compiler Shaders: Compiling...\n");
		AddCompile("ScreenPSTexture", ShaderType::Pixel);
		AddCompile("ScreenVSTexture", ShaderType::Vertex);

		AddCompile("ScreenPixelShader", ShaderType::Pixel);
		AddCompile("ScreenVertexShader", ShaderType::Vertex);

		AddCompile("PSFXAA", ShaderType::Pixel);
		AddCompile("VSFXAA", ShaderType::Vertex);



		LOG("State Compiler Shaders: Complete\n");
	}
	void ShaderCompilerWorker::AddCompile(const String& Name, ShaderType Type)
	{
		ShaderCompilerInput Input;
		Input.Type = Type;
		Input.Model = ShaderModel::SM5;
		Input.ShaderName = Name;


		StringView EntryPoint;
		if (Type == ShaderType::Pixel)
			EntryPoint = "PSMain";
		else if(Type == ShaderType::Vertex)
			EntryPoint = "VSMain";


		Input.EntryPoint = EntryPoint;
		ShaderCompilerOutput Output;
		CompileShader(Input, Output);

		if (Type == ShaderType::Pixel)
			GPSResourceMap.insert({ Name, GDynamicRHI->RHICreatePixelShader(Output.Code) });
		else if (Type == ShaderType::Vertex)
			GVSResourceMap.insert({ Name, GDynamicRHI->RHICreateVertexShader(Output.Code) });

		GShadersMap.insert({Name, Output});
	}
}