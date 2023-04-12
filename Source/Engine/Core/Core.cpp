

#include <Engine/Core/Core.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/Generic/Platform.h>

namespace GeometricEngine
{
	int GuardedMain(void* hInstance, const CHAR* CmdLine)
	{

		Platform::PreInit(hInstance);

		if (!Platform::Init())
		{

			return -1;
		}

		Application::InitializeProduct(CmdLine);

		while (!Application::ShouldExit())
		{

			Platform::Tick();

			Application::OnTick();

			//Application::OnFixedTick();

			//Application::OnLateTick();

			Application::OnDrawFrame();


			Sleep(1);
		}
		return 0;
	}
}	