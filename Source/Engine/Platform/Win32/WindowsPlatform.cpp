#include <Engine/Platform/Win32/WindowsPlatform.h>
#include <Engine/System/Time.h>

namespace MeteorEngine
{
	void WindowsPlatform::PreInit()
	{
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = &WindowsPlatform::WndProc;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wc.lpszClassName = __TEXT("MeteorEngine");
		wc.hIcon = 0;
		wc.hCursor = LoadCursor(GetModuleHandleA(NULL), IDC_ARROW);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.lpszMenuName = 0;
		wc.hIconSm = 0;
		RegisterClassEx(&wc);
		
	}

	Time WindowsPlatform::GetTime()
	{
		static LARGE_INTEGER m_time, m_highPerformanceFreq;
		QueryPerformanceFrequency(&m_highPerformanceFreq);
		QueryPerformanceCounter(&m_time);
		return Microseconds(m_time.QuadPart * 1000000 / m_highPerformanceFreq.QuadPart);
	}

	void WindowsPlatform::Tick()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	extern LRESULT WndProcHandler(HWND, UINT, WPARAM, LPARAM aram);
	LRESULT WindowsPlatform::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		if (msg == WM_CREATE)
		{
			/// Get Windows window instance (it was passed as the last argument of CreateWindow)
			LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;
			/// Set as the "user data" parameter of the window
			SetWindowLongPtrA(hWnd, GWLP_USERDATA, window);
		}
		WindowsWindow* window = hWnd ? reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)) : NULL;
		if (window)
			window->OnEvent(msg, wParam, lParam);


		if (msg == WM_CLOSE || (msg == WM_SYSCOMMAND) && (wParam == SC_KEYMENU))
		{
			PostQuitMessage(0);
			return 0;
		}

		return (hWnd != 0) ? DefWindowProcA(hWnd, msg, wParam, lParam) : 0;
	}
}