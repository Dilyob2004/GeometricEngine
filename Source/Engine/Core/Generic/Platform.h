#ifndef PLATFORM_H
#define PLATFORM_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Platform
	{
	public:
		static void PreInit(void*);



		static void* GetDLLModule(const CHAR*, const CHAR*);

		static void Tick();




	};
}
#endif // !PLATFORM_H
