#include <Engine/Core/Generic/FileSystem.h>
#include <Engine/Core/Windows/WindowsFileSystem.h>
namespace GeometricEngine
{
	bool FileSystem::MakeDirectory(const StringView& path)
	{
		return WindowsFileSystem::MakeDirectory(path);
	}
	bool FileSystem::Move(const StringView& bufferDst, const StringView& bufferSrc, bool overwrite)
	{
		return WindowsFileSystem::Move(bufferDst, bufferSrc, overwrite);
	}
	bool FileSystem::DeleteDirectory(const StringView& path)
	{
		return WindowsFileSystem::DeleteDirectory(path);
	}
	bool FileSystem::Delete(const StringView& path)
	{
		return WindowsFileSystem::Delete(path);

	}
}
