
#include "ShaderCompilerDX11.h"
#include <Engine/Core/Generic/File.h>
#include <Engine/Core/Generic/ScopeLock.h>
#include <Engine/Core/Generic/Path.h>
#include <d3dcompiler.h>

CriticalSection CriticalSectionFile;
bool LoadShaderFile(const String& ShaderName, TArray<CharAnsi>& Buffer)
{
	ScopeLock Locker(&CriticalSectionFile);

	String PathShader = SPath::GetEngineShadersDir() + "/";
	PathShader += ShaderName;
	PathShader += ".gsf";
	File* ShaderFile = File::Create(PathShader, FileMode::OpenExisting, FileAccess::Read, FileShare::Read);

	if (!ShaderFile)
		return false;

	Buffer.Resize(ShaderFile->GetSize());
	if (!ShaderFile->Read(Buffer.Pointer(), Buffer.Count(), NULL)) 
		return false;

	ShaderFile->Close();
	delete ShaderFile;
	ShaderFile = nullptr;

	return true;
}


void CompileShaderDX11(	const String& FileNameShader,
						const String& EntryPoint,
						const String& Target,
						TArray<U32>& OutputCode,
						TArray<String>& OutputError)
{
	TArray<CharAnsi> Buffer;
	if (!LoadShaderFile(FileNameShader, Buffer))
	{
		OutputError.Push("Failed to load shader file!");
		return;
	}
	ID3DBlob* pCode, * pErrors;
	HRESULT Result = D3DCompile(Buffer.Pointer(),
								Buffer.Count(),
								*FileNameShader,
								NULL,
								D3D_COMPILE_STANDARD_FILE_INCLUDE,
								*EntryPoint,
								*Target,
								D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
								0,
								&pCode,
								&pErrors);


	if (pErrors)
		if (pErrors->GetBufferSize() > 0)
		{
			TArray<CharAnsi> Buffer;
			Buffer.Resize(static_cast<I32>(pErrors->GetBufferSize()));
			SMemory::Copy(Buffer.Pointer(), pErrors->GetBufferPointer(), Buffer.Count());
			OutputError.Push(Buffer.Pointer());
			return;
		}

	OutputCode.Resize(static_cast<I32>(pCode->GetBufferSize()));
	SMemory::Copy(OutputCode.Pointer(), pCode->GetBufferPointer(), OutputCode.Count());
}
