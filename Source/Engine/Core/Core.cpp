

#include <Engine/Core/Core.h>
#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/EngineModule.h>

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/InputCore/InputCore.h>
namespace GeometricEngine
{
	int GuardedMain(void* hInstance, const CHAR* CmdLine)
	{
		Platform::PreInit(hInstance);



		if (!Application::InitializeProduct("Geometric Engine", CmdLine))
		{
			LOG("Fatal Error: Failed to Initizlied Application!");
			exit(-1);
		}
		EngineModule::OnInitialize();
		while (!Application::ShouldExit())
		{
			Platform::Tick();


			EngineModule::OnTick();


			EngineModule::OnLateTick();


			EngineModule::OnDraw();
			Sleep(1);
		}

		EngineModule::OnDeInitialize();
		return 0;
	}
}	