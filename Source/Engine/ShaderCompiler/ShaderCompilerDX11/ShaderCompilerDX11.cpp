
#include "ShaderCompilerDX11.h"
#include <Engine/Core/Generic/File.h>
#include <Engine/Core/Generic/ScopeLock.h>
#include <d3dcompiler.h>
namespace GeometricEngine
{
	CriticalSection CriticalSectionFile;
	bool LoadShaderFile(const String& ShaderName, TVector<CHAR>& Buffer)
	{
		ScopeLock Locker(&CriticalSectionFile);

		String PathShader = "../../Source/Shaders/";
		PathShader += ShaderName;
		PathShader += ".hlsl";
		File* ShaderFile = File::Create(PathShader, FileMode::OpenExisting, FileAccess::Read, FileShare::Read);

		if (!ShaderFile)
			return false;


		Buffer.Resize(ShaderFile->GetSize());
		if (!ShaderFile->Read(Buffer.Pointer(), Buffer.GetCount(), NULL))
			return false;

		ShaderFile->Close();
		return true;
	}
	void CompileShaderDX11(	const String& FileNameShader,
							const StringView& EntryPoint,
							const StringView& Target,
							TVector<U32>& OutputCode,
							TVector<CHAR>& OutputError)
	{
		TVector<CHAR> Buffer;
		if (!LoadShaderFile(FileNameShader, Buffer))
		{
			String Error = "Failed to load shader file!";
			for (int i = 0; i < Error.Size(); i++)
				OutputError.Push(Error[i]);
			return;
		}
		ID3DBlob* pCode, * pErrors;

		HRESULT Result = D3DCompile(Buffer.Pointer(),
									Buffer.GetCount(),
									FileNameShader.Pointer(),
									NULL,
									D3D_COMPILE_STANDARD_FILE_INCLUDE,
									EntryPoint.Pointer(),
									Target.Pointer(), 
									D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
									0,
									&pCode,
									&pErrors);


		if (pErrors)
		{
			if (pErrors->GetBufferSize() > 0)
			{
				OutputError.Resize(static_cast<I32>(pErrors->GetBufferSize()));
				SMemory::Copy(OutputError.Pointer(), pErrors->GetBufferPointer(), OutputError.GetCount());
			
				for (auto i : OutputError)
					std::cout << i;
				exit(-1);
			}
		}



		OutputCode.Resize(static_cast<I32>(pCode->GetBufferSize()));
		SMemory::Copy(OutputCode.Pointer(), pCode->GetBufferPointer(), OutputCode.GetCount());
	}
}