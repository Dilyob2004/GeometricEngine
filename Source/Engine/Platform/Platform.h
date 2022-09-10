#ifndef PLATFORM_H
#define PLATFORM_H
#include <Engine/Core/Config.h>
#include <Engine/System/Time.h>


namespace MeteorEngine
{
	class METEOR_API Platform
	{
	public:
		static void PreInit();
		static Time GetTime();
		static void* GetDllFunction(const char*, const char*);
		static void Tick();
	};
}
#endif // !PLATFORM_H
