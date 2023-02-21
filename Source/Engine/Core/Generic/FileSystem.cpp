#include <Engine/Core/Generic/FileSystem.h>
#include <Engine/Core/Windows/WindowsFileSystem.h>
namespace GeometricEngine
{
	bool FileSystem::CreateDirectoryIn(const std::string& path)
	{
		return WindowsFileSystem::CreateDirectoryIn(path);
	}
	bool FileSystem::MoveFileTo(const std::string& bufferDst, const std::string& bufferSrc, bool overwrite)
	{
		return WindowsFileSystem::MoveFileTo(bufferDst, bufferSrc, overwrite);
	}
	bool FileSystem::DeleteDirectory(const std::string& path)
	{
		return WindowsFileSystem::DeleteDirectory(path);
	}
	bool FileSystem::RemoveFile(const std::string& path)
	{
		return WindowsFileSystem::RemoveFile(path);

	}
	void FileSystem::Open(const Path& path)
	{
		WindowsFileSystem::Open(path);
	}
	void FileSystem::Close()
	{
		WindowsFileSystem::Close();
	}
	std::vector<Path> FileSystem::FindDirectory(Path path)
	{
		return WindowsFileSystem::FindDirectory(path);
	}
}
