#include <Engine/System/File.h>
#include <Engine/Platform/Win32/WindowsFile.h>

namespace MeteorEngine
{

	File* File::Open(const std::string& path, FileMode mode, FileAccess access, FileShare share)
	{
		return WindowsFile::Open(path, mode, access, share);
	}
}