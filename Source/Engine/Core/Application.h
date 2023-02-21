#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Application
	{
	public:
		static Application& GetInstance() { return *ApplicationInstance; }
		Application();
		virtual ~Application();
	private:
        static Application *			ApplicationInstance;
    };
}

#endif // APPLICATION_H
