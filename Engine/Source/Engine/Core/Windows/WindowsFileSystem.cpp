#include <Engine/Core/Windows/WindowsFileSystem.h> 
#include <Engine/Core/Misc/Log.h>

namespace GeometricEngine
{
	bool WindowsFileSystem::MakeDirectory(const StringView& Path)
	{
		return ::CreateDirectory(Path.Pointer(), NULL);
	}
	bool WindowsFileSystem::DirectoryExists(const StringView& Path)
	{
		const DWORD Result = GetFileAttributes(Path.Pointer());
		return Result != 0xFFFFFFFF && (Result & FILE_ATTRIBUTE_DIRECTORY);
	}
	bool WindowsFileSystem::Move(const StringView& BufferDst, const StringView& BufferSrc, bool Overwrite)
	{
		const DWORD Flags = MOVEFILE_COPY_ALLOWED | (Overwrite ? MOVEFILE_REPLACE_EXISTING : 0);
		return ::MoveFileEx(BufferSrc.Pointer(), BufferDst.Pointer(), Flags);
	}
	bool WindowsFileSystem::DeleteDirectory(const StringView& Path)
	{
		RemoveDirectory(Path.Pointer());
		const DWORD Result = GetFileAttributes(Path.Pointer());
		return Result != 0xFFFFFFFF && (Result & FILE_ATTRIBUTE_DIRECTORY);
	}
	bool WindowsFileSystem::Delete(const StringView& Path)
	{
		return ::DeleteFile(Path.Pointer());
	}
}

