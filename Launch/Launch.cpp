#include <Engine/Core/Core.h>
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
		PSTR		CmdLine = GetCommandLine();
	#endif
	return GeometricEngine::GuardedMain(hInstance, CmdLine);
}