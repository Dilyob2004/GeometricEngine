

#include <Engine/Core/Core.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	int GuardedMain(void* hInstance, const CHAR* CmdLine)
	{
		Platform::PreInit(hInstance);

		if (!Platform::Init())
		{
			LOG("Cannot Initialize Platform!");
			return -1;
		}

		Application::InitializeProduct(CmdLine);

		while (!Application::ShouldExit())
		{

			Platform::Tick();

			Application::OnTick();

			Application::OnFixedTick();

			Application::OnLateTick();

			Application::OnDrawFrame();
		}
		Application::OnExit();
		return 0;
	}
}	