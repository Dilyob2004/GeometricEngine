#include <Engine/Core/Windows/WindowsPlatform.h>=
#include <Engine/Core/Misc/Log.h>
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
		WindowClass.lpszClassName	= TEXT("MeteorEngine");
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
		HMODULE module = LoadLibraryA(moduleName);
		void* adress = (module != NULL) ? reinterpret_cast<void*>(GetProcAddress(module, name)) : NULL;
		if (!adress)
			return NULL;
		FreeLibrary(module);
		return adress;
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
	LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{


		if (msg == WM_CREATE)
		{
			LONG_PTR WindowUserData = (LONG_PTR) reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;			
			SetWindowLongPtr(hWnd, GWLP_USERDATA, WindowUserData);
		}
		/**WindowsWindow* window = hWnd ? reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)) : NULL;
		if (window) 
			window->OnEvent(msg, wParam, lParam);
			*/
		if (msg == WM_DESTROY)
		{
			PostQuitMessage(0);
			return 0;
		}
		return (hWnd != 0) ? DefWindowProcA(hWnd, msg, wParam, lParam) : 0;
	}
}