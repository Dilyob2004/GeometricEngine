#include "ShaderCompilerWorker.h"
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Generic/ScopeLock.h>
#include <Engine/Core/Generic/Platform.h>

CriticalSection CompileWorker;
std::map < String, RHIVertexShader* > GVertexShaderMap;
std::map < String, RHIPixelShader* >	GPixelShaderMap;

void ShaderCompileWorker::DefaultInitialize()
{

	ScopeLock Locker(&CompileWorker);

	LOG("Info: [SHADERCOMPILEWORKER] Compiling...\n");
	long long StartTime = Platform::GetTime();

	AddCompile(TEXT("ScreenPixelShader"), ShaderType::Pixel);
	AddCompile(TEXT("ScreenVertexShader"), ShaderType::Vertex);


	LOG(String::Format("Info: [SHADERCOMPILEWORKER] Time Elapsed: %lfms\n", F64(Platform::GetTime() - StartTime) / 1000.0f));
	
	LOG("Info: [SHADERCOMPILEWORKER] Compiled!\n");
}

void ShaderCompileWorker::AddCompile(const String& Name, ShaderType Type)
{
	ShaderCompilerInput Input;
	Input.Type = Type;
	Input.Model = ShaderModel::SM5;
	Input.ShaderName = Name;
	Input.EntryPoint = "Main";

	ShaderCompilerOutput Output;
	CompileShader(Input, Output);

	if (Output.Errors.NotEmpty())
	{
		LOG("Error: [SHADERCOMPILEWORKER] Failed Compiled!\n");
		for (String i : Output.Errors) 
			LOG(i + '\n');
		exit(-1);
	}

	if (Type == ShaderType::Pixel)
		GPixelShaderMap.insert({ Name, GDynamicRHI->RHICreatePixelShader(Output.Code) });


	else if (Type == ShaderType::Vertex)
		GVertexShaderMap.insert({ Name, GDynamicRHI->RHICreateVertexShader(Output.Code) });
}
