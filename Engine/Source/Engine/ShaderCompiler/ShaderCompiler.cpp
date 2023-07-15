#include <Engine/ShaderCompiler/ShaderCompiler.h>
#ifdef _WIN32
#include <Engine/ShaderCompiler/ShaderCompilerDX11/ShaderCompilerDX11.h>
#endif // WIN32

void CompileShader(const ShaderCompilerInput& Input, ShaderCompilerOutput& Output)
{
	Output.Type = Input.Type;
	Output.ShaderName = Input.ShaderName;
	if (Input.Model == ShaderModel::SM5)
	{
		switch (Input.Type)
		{
			case ShaderType::Pixel:
				CompileShaderDX11(Input.ShaderName, Input.EntryPoint, ("ps_5_0"), Output.Code, Output.Errors);
				return;
			case ShaderType::Vertex:
				CompileShaderDX11(Input.ShaderName, Input.EntryPoint, ("vs_5_0"), Output.Code, Output.Errors);
				return;
		}
	}
	else if (Input.Model == ShaderModel::SM4)
	{
		switch (Input.Type)
		{
			case ShaderType::Pixel:
				CompileShaderDX11(Input.ShaderName, Input.EntryPoint, ("ps_4_0"), Output.Code, Output.Errors);
				return;
			case ShaderType::Vertex:
				CompileShaderDX11(Input.ShaderName, Input.EntryPoint, ("vs_4_0"), Output.Code, Output.Errors);
				return;
		}
	}
}