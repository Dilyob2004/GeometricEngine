#include <Engine/Core/Generic/File.h>
#include <Engine/Core/Windows/WindowsFile.h>

File* File::Create(const String& Path, FileMode Mode, FileAccess Access, FileShare Share)
{
	return WindowsFile::Open(Path, Mode, Access, Share);
}