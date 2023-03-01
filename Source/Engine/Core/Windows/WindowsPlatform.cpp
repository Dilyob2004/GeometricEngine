#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Windows/WindowsWindow.h>
#include <Engine/Core/Windows/WindowsInput.h>
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Application.h>
namespace GeometricEngine
{
	HINSTANCE WindowsPlatform::HandleInstance = NULL;


	void WindowsPlatform::PreInit(void* hInstance)
	{
		HandleInstance = (HINSTANCE)hInstance;
		WNDCLASSEX WindowClass;
		ZeroMemory(&WindowClass, 0);
		WindowClass.cbSize			= sizeof(WNDCLASSEX);
		WindowClass.style			= CS_DBLCLKS;
		WindowClass.lpfnWndProc		= &WindowsPlatform::WndProc;
		WindowClass.hInstance		= HandleInstance;
		WindowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
		WindowClass.lpszClassName	= TEXT("GeometricEngine");
		WindowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		WindowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
		WindowClass.cbClsExtra		= 0;
		WindowClass.cbWndExtra		= 0;
		WindowClass.lpszMenuName    = 0;
		WindowClass.hIconSm			= 0;
		if (!RegisterClassEx(&WindowClass))
		{
			LOG("Error: [WINDOWS] Failed to Register class platform!");
			exit(-1);
		}
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
		MSG Message;
		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageW(&Message);
		}
	}
	LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT Msg, WPARAM WParam, LPARAM LParam)
	{
		WindowsWindow::WndProc(hWnd, Msg, WParam, LParam);

		if(WindowsInput::HasInitialized())
			WindowsInput::WndProc(hWnd, Msg, WParam, LParam);

		return DefWindowProcA(hWnd, Msg, WParam, LParam);
	}
}