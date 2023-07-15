#ifndef SHADERCOMPILER_H
#define SHADERCOMPILER_H

#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Misc/StringView.h>

enum class ShaderModel
{
	SM4, SM5, SM6
};
enum class ShaderType
{
	None,
	Pixel,
	Vertex,
	Geometry,
	Hull,
	Compute
};
struct ShaderCompilerInput
{
	ShaderModel Model = ShaderModel::SM5;
	ShaderType  Type = ShaderType::None;
	String		ShaderName;
	String		EntryPoint;
};
struct ShaderCompilerOutput
{
	TArray<U32>		Code;
	TArray<String>	Errors;
	ShaderType		Type = ShaderType::None;
	String			ShaderName;
};


GEOMETRIC_API void CompileShader(const ShaderCompilerInput& Input, ShaderCompilerOutput& Output);

#endif // !SHADERCOMPILER_H
