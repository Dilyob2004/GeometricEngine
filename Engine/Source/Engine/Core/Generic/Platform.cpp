#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Windows/WindowsPlatform.h>
typedef WindowsPlatform PlatformImpl;
void Platform::PreInit(void *HandleInstance)
{
	PlatformImpl::PreInit(HandleInstance);
}	
bool Platform::Init()
{
	return PlatformImpl::Init();
}
void Platform::Tick()
{
	PlatformImpl::Tick();
}
U128 Platform::GetTime()
{
	return PlatformImpl::GetTime();
}
void Platform::GetTime(FTimeItems& TimeItem)
{
	PlatformImpl::GetTime(TimeItem);
}
void Platform::GetUTCTime(FTimeItems& TimeItem)
{
	PlatformImpl::GetUTCTime(TimeItem);
}
void* Platform::GetDLLModule(const CharAnsi* ModuleName, const CharAnsi* NameFunction)
{
	return PlatformImpl::GetDLLModule(ModuleName, NameFunction);
}
bool Platform::MakeDirectory(const String& Path)
{
	return PlatformImpl::MakeDirectory(Path);
}
bool Platform::DirectoryExists(const String& Path)
{
	return PlatformImpl::DirectoryExists(Path);
}
bool Platform::MoveFileTo(const String& bufferDst, const String& bufferSrc, bool overwrite)
{
	return PlatformImpl::MoveFileTo(bufferDst, bufferSrc, overwrite);
}
bool Platform::CopyFileTo(const String& To, const String& From)
{
	return PlatformImpl::CopyFileTo(To, From);
}
bool Platform::DeleteDirectory(const String& path)
{
	return PlatformImpl::DeleteDirectory(path);
}
bool Platform::RemoveFile(const String& path)
{
	return PlatformImpl::RemoveFile(path);

}
bool Platform::FileExists(const String& Path)
{
	return PlatformImpl::FileExists(Path);
}

bool Platform::GetFilesFromDirectory(const String& Path, TArray<String>& Results)
{
	return PlatformImpl::GetFilesFromDirectory(Path, Results);
}
bool Platform::GetFilesFromDirectory(const String& Path, TArray<FPathInfo>& Results)
{
	return PlatformImpl::GetFilesFromDirectory(Path, Results);
}
bool Platform::GetFilesFromDirectoryAll(const String& Path, TArray<String>& Results)
{
	return PlatformImpl::GetFilesFromDirectoryAll(Path, Results);
}