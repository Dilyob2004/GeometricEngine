
#include <Engine/Core/Application.h>

#include <Engine/InputCore/InputModule.h>
#include <Engine/RHI/RHIModule.h>
namespace GeometricEngine
{
	MODULEINSTANCE(InputModule, GInputModule);
	MODULEINSTANCE(RHIModule, GRHIModule);
	Application* Application::ApplicationInstance = NULL;

	static Window* MainWindow = NULL;
	Application::Application()
	{
		ApplicationInstance = this;
	}
	Application::~Application()
	{

	}
	Window* Application::GetMainWindow()
	{
		return MainWindow;
	}
	bool Application::InitializeProduct(const CHAR* ApplicationName, const CHAR* CmdLine)
	{
		WindowDefinition		Info;
		Info.PositionX			= 200;
		Info.PositionY			= 200;
		Info.SizeWidth			= 800;
		Info.SizeHeight			= 600;
		Info.Title				= ApplicationName;
		Info.HasWindowBorder	= true;
		Info.IsRegularWindow	= false;
		MainWindow				= Window::Create(Info);
		return true;

	}
	bool Application::ShouldExit()
	{
		return MainWindow->IsClose();
	}
}