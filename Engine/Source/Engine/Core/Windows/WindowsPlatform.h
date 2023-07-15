#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H
#include <Engine/Core/Generic/PlatformInfo.h>
#include <Engine/Core/Generic/Path.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Containers/Array.h>
#include <Windows.h>
class GEOMETRIC_API WindowsPlatform
{
public:
	static HINSTANCE HandleInstance; 



	static void PreInit(void*);
	static bool Init();
	static RAMStats GetRAMStats();
	static CPUInfo GetCPUInfo();

	static String GetComputerStr();
	static String GetUserStr();

	static void Tick();


	static void* GetDLLModule(const CharAnsi*, const CharAnsi*);


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

	static bool GetFilesFromDirectory(const String& Path, TArray<FPathInfo>& Results);
	static bool GetFilesFromDirectory(const String& Path, TArray<String>& Results);
	static bool GetFilesFromDirectoryAll(const String& Path, TArray<String>& Results);
private:

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

};

#endif