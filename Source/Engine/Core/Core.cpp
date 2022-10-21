#include <Engine/Core/Core.h>
#include <Engine/Core/Application.h>
#include <Engine/Platform/Platform.h>
namespace MeteorEngine
{
	int Main(const CommandLineSpec& cmdLine)
	{
		Platform::PreInit();
		/**if (!CommandLine::Parse(cmdLine))
		{
			LOG("Failed to Parse command line!");
			return -1;
		}*/
		Application* app = new Application();
		app->Run();
		delete app;


		return 0;
	}
}