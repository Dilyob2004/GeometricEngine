
#include <Engine/Core/Application.h>

#include <Engine/ImageCore/ImageCore.h>

#include <Engine/InputCore/InputModule.h>
#include <Engine/RHI/RHIModule.h>
#include <Engine/InputCore/InputCore.h>
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
		Info.HasBorder			= true;
		Info.IsRegularWindow	= false;
		MainWindow				= Window::Create(Info);

		Image ApplicationIcon;
		if (ApplicationIcon.Load("../../Content/Logo/64x64.png"))
			MainWindow->SetIcon(ApplicationIcon.GetData(), ApplicationIcon.GetWidth(), ApplicationIcon.GetHeight());
		
		return true;

	}
	bool Application::ShouldExit()
	{
		return InputWindow::OnClosed();
	}
}