#include <Engine/Platform/Platform.h>


#include <Engine/Platform/Windows/WindowsPlatform.h>
namespace MeteorEngine
{


	void Platform::PreInit()
	{
		WindowsPlatform::PreInit();
	}
	void* Platform::Memzero(void* pointer, u32 size)
	{
		return WindowsPlatform::Memzero(pointer, size);
	}
	void Platform::Tick()
	{
		WindowsPlatform::Tick();
	}
	Time Platform::GetTime()
	{
		return WindowsPlatform::GetTime();
	}
	void* Platform::GetDllFunction(const char* module, const char* name)
	{
		return WindowsPlatform::GetDllFunction(module, name);
	}
}
