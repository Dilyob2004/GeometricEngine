#include "WindowsPlatform.h"
#include "WindowsWindow.h"
#include "WindowsInput.h"
#include <ImGui/imgui_impl_win32.h>
#include <Engine/Core/Misc/Log.h>
#include <Psapi.h>
#include <intrin.h>
#include "../../Intermediate/Projects/resource.h"
String ComputerName, UserName;
CPUInfo cInfo;
HINSTANCE WindowsPlatform::HandleInstance = NULL;

DWORD CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = static_cast<ULONG_PTR>(1) << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

void WindowsPlatform::PreInit(void* hInstance)
{
	#if (defined DEBUG_EDITOR || RELEASE_EDITOR)
		ImGui_ImplWin32_EnableDpiAwareness();
	#endif

	HandleInstance = (HINSTANCE)hInstance;

	WNDCLASSEX WindowClass;
	ZeroMemory(&WindowClass, sizeof(WindowClass));
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style			= CS_DBLCLKS;
	WindowClass.lpfnWndProc		= &WindowsPlatform::WndProc;
	WindowClass.hInstance		= HandleInstance;
	WindowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	WindowClass.lpszClassName	= TEXT("GeometricEngine");
	
	WindowClass.hIcon			= LoadIcon(HandleInstance, MAKEINTRESOURCE(ENGINEBIG));
	WindowClass.hIconSm			= LoadIcon(HandleInstance, MAKEINTRESOURCE(ENGINESMALL));

	WindowClass.hCursor			= LoadCursor(HandleInstance, IDC_ARROW);
	if (!RegisterClassEx(&WindowClass))
	{
		LOG("Error: [PLATFORM] Failed to Register class platform!\n");
		exit(-1);
	}
}
RAMStats WindowsPlatform::GetRAMStats()
{
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);
	GlobalMemoryStatusEx(&MemStatus);

	RAMStats Result;
	Result.TotalPhysical = MemStatus.ullTotalPhys;
	Result.TotalVirtual	 = MemStatus.ullTotalVirtual;
	Result.UsedPhysical	 = MemStatus.ullTotalPhys - MemStatus.ullAvailPhys;
	Result.UsedVirtual	 = MemStatus.ullTotalVirtual - MemStatus.ullAvailVirtual;
	return Result;
}
String  WindowsPlatform::GetComputerStr()
{
	return ComputerName;
}
String  WindowsPlatform::GetUserStr()
{
	return UserName;
}

bool WindowsPlatform::Init()
{

	///CPU Info
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer = NULL;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pBuffer = NULL;
	DWORD ReturnLength = 0;
	DWORD LogicalCount = 0;
	DWORD CoreCount = 0;
	DWORD L1CacheSize = 0;
	DWORD L2CacheSize = 0;
	DWORD L3CacheSize = 0;
	DWORD PackageCount = 0;
	DWORD ByteOffset = 0;
	PCACHE_DESCRIPTOR Cache;
	BOOL Done = FALSE;

	while (!Done)
	{
		DWORD Result = GetLogicalProcessorInformation(Buffer, &ReturnLength);
		if (!Result)
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (Buffer)
					SMemory::Free(Buffer);
				Buffer = static_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION>(malloc(ReturnLength));
				if (!Buffer)
					return false;
			}
			else
				return false;
		}
		else
			Done = TRUE;
	}
	pBuffer = Buffer;

	while (ByteOffset + sizeof(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= ReturnLength)
	{
		switch (pBuffer->Relationship)
		{
			case RelationProcessorCore:

				CoreCount++;
				LogicalCount += CountSetBits(pBuffer->ProcessorMask);
				break;

			case RelationCache:
				Cache= &pBuffer->Cache;
				if (Cache->Level == 1)
					L1CacheSize += Cache->Size;
				else if (Cache->Level == 2)
					L2CacheSize += Cache->Size;
				else if (Cache->Level == 3)
					L3CacheSize += Cache->Size;
				break;
			case RelationProcessorPackage:
				PackageCount++;
				break;
		}
		ByteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		pBuffer++;
	}
	free(Buffer);        
		
	int iCPUInfo[4] = { -1 };
	char CPUBrandString[0x40];

	/// Get the information associated with each extended ID.
	__cpuid(iCPUInfo, 0x80000000);
	U32 nExIds = iCPUInfo[0];
	for (U32 i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(iCPUInfo, i);
		/// Interpret CPU brand string
		if (i == 0x80000002)
			SMemory::Copy(CPUBrandString, iCPUInfo, sizeof(iCPUInfo));
		else if (i == 0x80000003)
			SMemory::Copy(CPUBrandString + 16, iCPUInfo, sizeof(iCPUInfo));
		else if (i == 0x80000004)
			SMemory::Copy(CPUBrandString + 32, iCPUInfo, sizeof(iCPUInfo));
	}


	SMemory::Copy(cInfo.Name, CPUBrandString, sizeof(CPUBrandString));

	cInfo.CoreCount = CoreCount;
	cInfo.LogicalCount = LogicalCount;
	cInfo.L1CacheSize = L1CacheSize;
	cInfo.L2CacheSize = L2CacheSize;
	cInfo.L3CacheSize = L3CacheSize;
	cInfo.PackageCount = PackageCount;

	CharAnsi szComp[256];
	DWORD Size = 0;

	if (GetComputerName(szComp, &Size))
		ComputerName = szComp;

		
	if (GetUserName(szComp, &Size))
		UserName = szComp;

	WindowsInput::Initialize();


	LOG("Info: [PLATFORM] Initialized!\n");
	return true;
}
CPUInfo WindowsPlatform::GetCPUInfo()
{
	return cInfo;
}
void* WindowsPlatform::GetDLLModule(const CharAnsi* moduleName, const CharAnsi* name)
{
	HMODULE Library = LoadLibrary(moduleName);

	if (!Library)
		return NULL;
	void* Adress =  reinterpret_cast<void*>(GetProcAddress(Library, name));

	if (!Adress)
		return NULL;

	FreeLibrary(Library);
	return Adress;
}

U128 WindowsPlatform::GetTime()
{
	LARGE_INTEGER Cycles, CyclesFreq;
	QueryPerformanceCounter(&Cycles);
	QueryPerformanceFrequency(&CyclesFreq);
	return Cycles.QuadPart * 1000000 / CyclesFreq.QuadPart;
}

void WindowsPlatform::GetTime(FTimeItems& TimeItem)
{
	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);
	TimeItem.Years			= SysTime.wYear;
	TimeItem.Month			= SysTime.wMonth;
	TimeItem.Week			= SysTime.wDayOfWeek;
	TimeItem.Day			= SysTime.wDay;
	TimeItem.Hour			= SysTime.wHour;
	TimeItem.Minute			= SysTime.wMinute;
	TimeItem.Second			= SysTime.wSecond;
	TimeItem.MilliSecond	= SysTime.wMilliseconds;

}
void WindowsPlatform::GetUTCTime(FTimeItems& TimeItem)
{
	SYSTEMTIME SysTime;
	::GetSystemTime(&SysTime);
	TimeItem.Years			= SysTime.wYear;
	TimeItem.Month			= SysTime.wMonth;
	TimeItem.Week			= SysTime.wDayOfWeek;
	TimeItem.Day			= SysTime.wDay;
	TimeItem.Hour			= SysTime.wHour;
	TimeItem.Minute			= SysTime.wMinute;
	TimeItem.Second			= SysTime.wSecond;
	TimeItem.MilliSecond	= SysTime.wMilliseconds;
}
void WindowsPlatform::Tick()
{
	WindowsInput::Tick();

	MSG Message;
	while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}
LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
{
	#if (defined DEBUG_EDITOR || RELEASE_EDITOR)
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Msg, WParam, LParam))
			return true;
	#else
		WindowsInput::WndProc(hWnd, Msg, WParam, LParam);
	#endif


	if (Msg == WM_CLOSE) 
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, Msg, WParam, LParam);
}
bool WindowsPlatform::MakeDirectory(const String& Path)
{
	return ::CreateDirectory(*Path, NULL);
}
bool WindowsPlatform::DirectoryExists(const String& Path)
{
	const DWORD Result = GetFileAttributes(Path.Pointer());
	return Result != 0xFFFFFFFF && (Result & FILE_ATTRIBUTE_DIRECTORY);
}
bool WindowsPlatform::MoveFileTo(const String& BufferDst, const String& BufferSrc, bool Overwrite)
{
	const DWORD Flags = MOVEFILE_COPY_ALLOWED | (Overwrite ? MOVEFILE_REPLACE_EXISTING : 0);
	return ::MoveFileEx(*BufferSrc, *BufferDst, Flags);
}
bool WindowsPlatform::CopyFileTo(const String& To, const String& From)
{
	return ::CopyFile(*To, *From, FALSE);

}
bool WindowsPlatform::FileExists(const String& Path)
{
	const DWORD Result = GetFileAttributes(*Path);
	return Result != 0xFFFFFFFF && !(Result & FILE_ATTRIBUTE_DIRECTORY);
}
bool WindowsPlatform::DeleteDirectory(const String& Path)
{
	::RemoveDirectory(*Path);
	const DWORD Result = GetFileAttributes(*Path);
	return Result != 0xFFFFFFFF && (Result & FILE_ATTRIBUTE_DIRECTORY);
}
bool WindowsPlatform::RemoveFile(const String& Path)
{
	return ::DeleteFile(*Path);
}
bool WindowsPlatform::GetFilesFromDirectory(const String& Path, TArray<String>& Results)
{

	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA  FindData = WIN32_FIND_DATA();

	FindHandle = FindFirstFile(*(Path / "*"), &FindData);

	if (FindHandle == INVALID_HANDLE_VALUE) 
		return false;

	while (FindNextFile(FindHandle, &FindData))
	{
		if (!CString::Compare(FindData.cFileName, ".."))
			continue;
		if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			Results.Push(Path / FindData.cFileName);
	}

	FindClose(FindHandle);
	if (GetLastError() == ERROR_NO_MORE_FILES)
		return true;
	return false;
}
bool WindowsPlatform::GetFilesFromDirectory(const String& Path, TArray<FPathInfo>& Results)
{

	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA  FindData = WIN32_FIND_DATA();

	FindHandle = FindFirstFile(*(Path / "*"), &FindData);

	if (FindHandle == INVALID_HANDLE_VALUE) 
	{
		return false;
	}

	while (FindNextFile(FindHandle, &FindData))
	{
		if (!CString::Compare(FindData.cFileName, ".."))
			continue;
		FPathInfo Info;
		Info.Name = FindData.cFileName;
		Info.IsDirectory = (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
		Results.Push(Info);	
	}

	FindClose(FindHandle);
	if (GetLastError() == ERROR_NO_MORE_FILES)
		return true;
	return false;
}


bool WindowsPlatform::GetFilesFromDirectoryAll(const String& Path, TArray<String>& Results)
{
	GetFilesFromDirectory(Path, Results);
	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA  FindData = WIN32_FIND_DATA();

	FindHandle = FindFirstFile(*(Path / "*"), &FindData);

	if (FindHandle == INVALID_HANDLE_VALUE)
		return false;

	while (FindNextFile(FindHandle, &FindData))
	{
		if (!CString::Compare(FindData.cFileName, ".."))
			continue;
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (GetFilesFromDirectoryAll(Path / FindData.cFileName, Results))
			{
				FindClose(FindHandle);
				return true;
			}

		}
	}

	FindClose(FindHandle);

	return false;
}