#include "WindowsPlatform.h"
#include "WindowsWindow.h"
#include "WindowsInput.h"
#include <Engine/Core/Application.h>
#include <ImGui/imgui_impl_win32.h>
#include <Engine/Core/Misc/Log.h>
#include <Psapi.h>
#include <intrin.h>
namespace GeometricEngine
{
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
		ImGui_ImplWin32_EnableDpiAwareness();

		HandleInstance = (HINSTANCE)hInstance;
		WNDCLASS WindowClass;
		ZeroMemory(&WindowClass, sizeof(WindowClass));
		WindowClass.style			= CS_DBLCLKS;
		WindowClass.lpfnWndProc		= &WindowsPlatform::WndProc;
		WindowClass.hInstance		= HandleInstance;
		WindowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
		WindowClass.lpszClassName	= TEXT("GeometricEngine");
		WindowClass.hIcon			= LoadIcon(HandleInstance, IDI_APPLICATION);
		WindowClass.hCursor			= LoadCursor(HandleInstance, IDC_ARROW);
		if (!RegisterClass(&WindowClass))
		{
			LOG("Error: [WINDOWS] Failed to Register class platform!");
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

		CHAR szComp[256];
		DWORD Size;

		if (GetComputerName(szComp, &Size))
			ComputerName = szComp;

		
		if (GetUserName(szComp, &Size))
			UserName = szComp;

		WindowsInput::Initialize();
		return true;
	}
	CPUInfo WindowsPlatform::GetCPUInfo()
	{
		return cInfo;
	}
	void* WindowsPlatform::GetDLLModule(const CHAR* moduleName, const CHAR* name)
	{
		HMODULE Library = LoadLibraryA(moduleName);

		if (!Library)
			return NULL;
		void* Adress = reinterpret_cast<void*>(GetProcAddress(Library, name)) ;

		if (!Adress)
			return NULL;

		FreeLibrary(Library);
		return Adress;
	}
	void WindowsPlatform::Tick()
	{
		WindowsInput::Tick();

		MSG Message;
		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageW(&Message);
		}
	}
	LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
	{

		WindowsInput::WndProc(hWnd, Msg, WParam, LParam);

		if (ImGui_ImplWin32_WndProcHandler(hWnd, Msg, WParam, LParam))
			return true;

		if (Msg == WM_CLOSE) 
		{
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProcA(hWnd, Msg, WParam, LParam);
	}
}