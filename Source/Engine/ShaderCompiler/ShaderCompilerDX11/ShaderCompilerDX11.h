#ifndef SHADERCOMPILERDX11_H
#define SHADERCOMPILERDX11_H
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Misc/StringView.h>

namespace GeometricEngine
{
	GEOMETRIC_API void CompileShaderDX11(	const String& Path,
											const StringView& EntryPoint,
											const StringView& Target,
											TVector<U32>& OutputCode,
											TVector<CHAR>& OutputError);
}
#endif // !SHADERCOMPILERDX11_H
