#include "Engine.h"

#include <Engine/Core/Misc/Log.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/ImageCore/ImageCore.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/Renderer/Renderer2D.h>

TScopePtr<Window> Engine::MainWindow = NULL;
RHIViewport* Engine::MainViewport = NULL;

static FLevel* EmptyLevel;
void Engine::InitializeProduct(const CharAnsi* CmdLine)
{
	if (!InitializeDynamicRHI())
	{
		LOG("Fatal Error: Failed to Initizlied DynamicRHI!\n");
		exit(-1);
	}

	ShaderCompileWorker::DefaultInitialize();



	WindowDefinition Info;
	Info.SizeWidth = 1280;
	Info.SizeHeight = 720;
	Info.Title		= TEXT("Geometric Engine");
	Info.Fullscreen = false;

	MainWindow.reset(Window::Create(Info));
	{
		Image ApplicationIcon;
		if (ApplicationIcon.Load(TEXT("../../Content/Logo/64x64.png")))
			MainWindow->SetIcon(ApplicationIcon.GetData(), ApplicationIcon.GetWidth(), ApplicationIcon.GetHeight());
	}

	RHIViewportDefinition Definition;
	Definition.Width = MainWindow->GetWidth();
	Definition.Height = MainWindow->GetHeight();
	Definition.HandleWindow = MainWindow->GetHandle();
	Definition.FullScreen = Info.Fullscreen;

	MainViewport = GDynamicRHI->RHICreateViewport(Definition);

	Renderer2D::Init();
	EmptyLevel = new FLevel("DefaultLevel");

	EmptyLevel->Deserialize("../../Content/Default.map");
}
bool Engine::ShouldExit()
{
	return Input::OnWindowClosed();
}

void Engine::OnTick()
{
	EmptyLevel->OnTick();
	if (Input::OnWindowResized()) 
	{
		GDynamicRHI->RHIResizeViewport(MainViewport, MainWindow->GetWidth(), MainWindow->GetHeight(), false);
		EmptyLevel->OnResize({ (F32)MainWindow->GetWidth(), (F32)MainWindow->GetHeight() });
	}
}
void Engine::OnDrawFrame()
{
	GDynamicRHI->RHIBeginFrameViewport(MainViewport);
		EmptyLevel->OnDrawActors();

	GDynamicRHI->RHIEndFrameViewport(MainViewport);
}
