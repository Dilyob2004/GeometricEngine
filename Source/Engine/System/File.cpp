#include <Engine/System/File.h>
#include <Engine/Platform/Windows/WindowsFile.h>

namespace MeteorEngine
{

	File* File::Create(const std::string& path, FileMode mode, FileAccess access, FileShare share)
	{
		return WindowsFile::Open(path, mode, access, share);
	}
}