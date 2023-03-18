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
		Pixel,
		Vertex,
		Geometry,
		Hull,
		Compute
	};
	struct ShaderCompilerInput
	{
		ShaderModel Model;
		String		ShaderName;
		StringView	EntryPoint;
		ShaderType  Type;
	};
	struct ShaderCompilerOutput
	{
		TVector<U32> Code;
		TVector<CHAR> Errors;
	};


	GEOMETRIC_API void CompileShader(const ShaderCompilerInput& Input, ShaderCompilerOutput& Output);
}
#endif // !SHADERCOMPILER_H
