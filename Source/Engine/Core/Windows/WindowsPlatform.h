#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	class GEOMETRIC_API WindowsPlatform
	{
	public:
		static HINSTANCE HandleInstance;
	public:
		static HINSTANCE GetHandleInstance() { return HandleInstance; }

		static void PreInit(void*);
		static bool Init();
		static void Tick();
		
		static void* GetDLLModule(const CHAR*, const CHAR*);


	private:

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	};
}
#endif