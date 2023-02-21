#include <Engine/Core/Windows/WindowsPlatform.h>
#include <Engine/Core/Generic/Platform.h>
namespace GeometricEngine
{
	void Platform::PreInit(void *HandleInstance)
	{
		WindowsPlatform::PreInit(HandleInstance);
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
