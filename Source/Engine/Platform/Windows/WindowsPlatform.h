#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H
#include <Engine/Platform/Windows/WindowsWindow.h>
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
		static void* Memzero(void*, u32);
		static Time GetTime();
		static void* GetDllFunction(const char*, const char*);
	protected:

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	};
}
#endif