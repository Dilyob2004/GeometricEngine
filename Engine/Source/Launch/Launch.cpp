#include <Engine/Core/Core.h>

extern "C"  { _declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001; }
extern "C"  { __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }
#ifdef GEOMETRIC_DEBUG
int main(int argc, char* argv[])
#else
int WINAPI WinMain(	_In_		HINSTANCE	hInstance,
					_In_opt_	HINSTANCE	hPrevInstance,
					_In_		PSTR		CmdLine,
					_In_		int		CmdShow)
#endif
{
	#ifdef GEOMETRIC_DEBUG
		HINSTANCE hInstance = GetModuleHandle(NULL);
		PSTR		CmdLine = GetCommandLineA();
	#endif

	try
	{
		return GeometricEngine::GuardedMain(hInstance, CmdLine);
	}
	catch (...)
	{
		return -1;
	}
}