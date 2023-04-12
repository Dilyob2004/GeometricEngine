#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Generic/Platform.h>
namespace GeometricEngine
{
	void Platform::PreInit(void *HandleInstance)
	{
		WindowsPlatform::PreInit(HandleInstance);
	}	
	bool Platform::Init()
	{
		return WindowsPlatform::Init();
	}
	void Platform::Tick()
	{
		WindowsPlatform::Tick();
	}
	void* Platform::GetDLLModule(const CHAR* ModuleName, const CHAR* NameFunction)
	{
		return WindowsPlatform::GetDLLModule(ModuleName, NameFunction);
	}
}
