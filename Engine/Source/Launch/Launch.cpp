#include <Engine/Core/Core.h>

#include <Windows.h>

#if defined DEBUG_EDITOR || DEBUG_GAME
int main()
#else
int WINAPI WinMain(_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		PSTR		CmdLine,
	_In_		int		CmdShow)
#endif
{

	#if defined DEBUG_EDITOR || DEBUG_GAME
		HINSTANCE hInstance = GetModuleHandle(NULL);
		CHAR* CmdLine = GetCommandLine();
	#endif
	try
	{
		return ::GuardedMain(hInstance, CmdLine);
	}
	catch (...)
	{
		return -1;
	}
}