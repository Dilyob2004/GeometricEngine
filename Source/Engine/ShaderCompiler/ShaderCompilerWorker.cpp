#include "ShaderCompilerWorker.h"

namespace GeometricEngine
{
	std::map<String, ShaderCompilerOutput> GShadersMap;
	void ShaderCompilerWorker::Initialize()
	{
		AddCompile("ScreenVSTexture", ShaderType::Vertex);
		AddCompile("ScreenPSTexture", ShaderType::Pixel);
		AddCompile("FXAA", ShaderType::Pixel);
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
		GShadersMap.insert({Name, Output});
	}
}