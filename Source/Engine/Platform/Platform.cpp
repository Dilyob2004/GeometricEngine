#include <Engine/Platform/Platform.h>


#include <Engine/Platform/Win32/WindowsPlatform.h>
namespace MeteorEngine
{


	void Platform::PreInit()
	{
		WindowsPlatform::PreInit();
	}
	void Platform::Tick()
	{
		WindowsPlatform::Tick();
	}
	Time Platform::GetTime()
	{
		return WindowsPlatform::GetTime();
	}
}
