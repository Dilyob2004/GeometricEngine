#ifndef SHADERCOMPILER_H
#define SHADERCOMPILER_H

#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Misc/StringView.h>

namespace GeometricEngine
{

	enum class ShaderModel
	{
		SM4, SM5
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
		ShaderModel Model = ShaderModel::SM4;
		ShaderType  Type = ShaderType::None;
		String		ShaderName;
		StringView	EntryPoint;
	};
	struct ShaderCompilerOutput
	{
		TVector<U32> Code;
		TVector<CHAR> Errors;
		ShaderType  Type = ShaderType::None;
		String		ShaderName;
	};


	GEOMETRIC_API void CompileShader(const ShaderCompilerInput& Input, ShaderCompilerOutput& Output);
}
#endif // !SHADERCOMPILER_H
