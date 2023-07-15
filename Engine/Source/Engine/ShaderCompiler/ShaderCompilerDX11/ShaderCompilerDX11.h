#ifndef SHADERCOMPILERDX11_H
#define SHADERCOMPILERDX11_H
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/String.h>

GEOMETRIC_API void CompileShaderDX11(	const String& Path,
										const String& EntryPoint,
										const String& Target,
										TArray<U32>& OutputCode,
										TArray<String>& OutputError);

#endif // !SHADERCOMPILERDX11_H
