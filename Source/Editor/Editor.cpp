#include "Editor.h"

#include <Engine/Core/Misc/Log.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/ImageCore/ImageCore.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
namespace GeometricEngine
{
	TSharedPtr<Window> Editor::MainWindow = NULL;
	TSharedPtr<RHIViewport> Editor::MainViewport = NULL;
	TSharedPtr<SceneViewport> Editor::SceneRenderer = NULL;


	void Editor::InitializeProduct(const CHAR* CmdLine)
	{
		LOG(CmdLine);
		if (!InitializeDynamicRHI())
		{
			LOG("Fatal Error: Failed to Initizlied DynamicRHI!\n");
			exit(-1);
		}

		ShaderCompilerWorker::Initialize();

		WindowDefinition Info;
		Info.PositionX = 200;
		Info.PositionY = 200;
		Info.SizeWidth = 1280;
		Info.SizeHeight = 720;
		Info.Title = "Geometric Editor";
		Info.HasBorder = true;
		Info.IsRegularWindow = false;


		MainWindow.reset(Window::Create(Info));

		{
			Image ApplicationIcon;
			if (ApplicationIcon.Load("../../Content/Logo/64x64.png"))
				MainWindow->SetIcon(ApplicationIcon.GetData(), ApplicationIcon.GetWidth(), ApplicationIcon.GetHeight());
		}

		RHIViewportDefinition Definition;
		Definition.Width = MainWindow->GetWidth();
		Definition.Height = MainWindow->GetHeight();
		Definition.HandleWindow = MainWindow->GetHandle();

		MainViewport.reset(GDynamicRHI->RHICreateViewport(Definition));
		SceneRenderer.reset(new SceneViewport());

		GDynamicRHI->RHICreateGUI(MainWindow->GetHandle());

		
	}
	bool Editor::ShouldExit()
	{
		return Input::OnWindowClosed();
	}

	void Editor::OnTick()
	{
		if (Input::OnWindowResized())
			GDynamicRHI->RHIResizeViewport(MainViewport.get(), MainWindow->GetWidth(), MainWindow->GetHeight(), false);

	}
	void Editor::OnDrawFrame()
	{

		SceneRenderer->OnDrawRenderer();



		GDynamicRHI->RHIBeginFrameViewport(MainViewport.get());

		GDynamicRHI->RHIBeginFrameGUI();
			SceneRenderer->OnDrawSceneViewport();
		GDynamicRHI->RHIEndFrameGUI();
		GDynamicRHI->RHIEndFrameViewport(MainViewport.get());

	}
}