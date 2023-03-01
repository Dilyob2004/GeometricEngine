

#include <Engine/Core/Core.h>
#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/EngineModule.h>
#include <Engine/InputCore/InputCore.h>
namespace GeometricEngine
{
	int GuardedMain(void* hInstance, const CHAR* CmdLine)
	{
		Platform::PreInit(hInstance);

		EngineModule::OnInitialize();


		if (!Application::InitializeProduct("Geometric Engine", CmdLine))
		{
			LOG("Fatal Error: Failed to Initizlied Application!");
			exit(-1);
		}


		while (!Application::ShouldExit())
		{
			EngineModule::OnTick();

			if (Input::GetMouseButtonDown(MouseCode::ButtonLeft))
				LOG("Pressed Left Button Mouse!");

			EngineModule::OnLateTick();
			Platform::Tick();
			Sleep(1);
		}

		EngineModule::OnDeInitialize();
		return 0;
	}
}	