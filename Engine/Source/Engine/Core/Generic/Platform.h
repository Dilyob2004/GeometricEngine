#ifndef PLATFORM_H
#define PLATFORM_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Generic/Path.h>

class GEOMETRIC_API Platform
{
public:
	static void PreInit(void*);
	static bool Init();

	static void* GetDLLModule(const CharAnsi*, const CharAnsi*);

	static void Tick();
	static U128 GetTime();

	static void GetTime(FTimeItems&);
	static void GetUTCTime(FTimeItems&);




	static bool MakeDirectory(const String& Path);
	static bool DeleteDirectory(const String& Path);
	static bool DirectoryExists(const String& Path);

	static bool MoveFileTo(const String&, const String&, bool);
	static bool CopyFileTo(const String& To, const String& From);
	static bool RemoveFile(const String& Path);
	static bool FileExists(const String& Path);


	static bool GetFilesFromDirectory(const String& Path, TArray<String>& Results);
	static bool GetFilesFromDirectory(const String& Path, TArray<FPathInfo>& Results);
	static bool GetFilesFromDirectoryAll(const String& Path, TArray<String>& Results);


};

#endif // !PLATFORM_H
