#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H
#include <Engine/Core/Generic/PlatformInfo.h>
#include <Engine/Core/Misc/String.h>
namespace GeometricEngine
{
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
		


		static void* GetDLLModule(const CHAR*, const CHAR*);


	private:

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	};
}
#endif