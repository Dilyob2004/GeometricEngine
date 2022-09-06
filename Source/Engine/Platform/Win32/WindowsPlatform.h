#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include <Engine/Platform/Win32/WindowsPlatform.h>
#include <Engine/Platform/Win32/WindowsWindow.h>
#include <Engine/System/Time.h>
namespace MeteorEngine
{
	class METEOR_API WindowsPlatform
	{
	public:
		WindowsPlatform() = default;
		~WindowsPlatform() = default;
		static void PreInit();
		static void Tick();
		static Time GetTime();
	protected:

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	};
}
#endif