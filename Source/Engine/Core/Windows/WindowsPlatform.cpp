#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsInput.h>
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Application.h>
#include <ImGui/imgui_impl_win32.h>
namespace GeometricEngine
{
	HINSTANCE WindowsPlatform::HandleInstance = NULL;


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
	struct RAMStats
	{
		U64 TotalPhysicalMemory;
		U64 UsedPhysicalMemory;
	};
	RAMStats GetRAMStats()
	{
		RAMStats Result;
		MEMORYSTATUSEX MemStatus;
		MemStatus.dwLength = sizeof(MemStatus);
		GlobalMemoryStatusEx(&MemStatus);
		Result.TotalPhysicalMemory = MemStatus.ullTotalPhys;
		Result.UsedPhysicalMemory = (MemStatus.ullTotalPhys - MemStatus.ullAvailPhys);
		return Result;
	}
	bool WindowsPlatform::Init()
	{
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		std::cout << "Clock Frequency: " << Frequency.QuadPart << "\n";
		WindowsInput::Initialize();

		return true;
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