#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Generic/Window.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Application
	{
	public:
		static Application* GetInstance() { return ApplicationInstance; }
		Application();
		virtual ~Application();
		static Window* GetMainWindow();
		static bool InitializeProduct(const CHAR* ApplicationName, const CHAR* CmdLine);
		static bool ShouldExit();
	private:
        static Application* ApplicationInstance;
    };
}

#endif // APPLICATION_H
