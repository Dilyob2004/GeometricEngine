#include <Engine/Core/Core.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Win32/WindowsPlatform.h>
namespace MeteorEngine
{
	int Main(CommandLine cmdLine)
	{
		WindowsPlatform::PreInit();
		Application* app = new Application();
		app->Run();
		delete app;
		return 0;
	}
}