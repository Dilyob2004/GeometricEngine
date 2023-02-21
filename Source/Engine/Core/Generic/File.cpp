#include <Engine/Core/Generic/File.h>
#include <Engine/Core/Windows/WindowsFile.h>

namespace GeometricEngine
{

	File* File::Create(const std::string& path, FileMode mode, FileAccess access, FileShare share)
	{
		return WindowsFile::Open(path, mode, access, share);
	}
}