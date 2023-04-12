#include "Engine.h"

#include <Engine/Core/Misc/Log.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/ImageCore/ImageCore.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/Renderer/Camera.h>
namespace GeometricEngine
{
	TSharedPtr<Window> Engine::MainWindow = NULL;
	TSharedPtr<RHIViewport> Engine::MainViewport = NULL;

	RHIBlendState* GBlendState;
	RHIRasterizerState* GRasterizerState;
	RHIDepthStencilState* GDepthStencilState;

	void Engine::InitializeProduct(const CHAR* CmdLine)
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
		Info.Title		= "Geometric Engine";
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
		GBlendState = GDynamicRHI->RHICreateBlendState(RHIBlendStateDefinition());
		GRasterizerState = GDynamicRHI->RHICreateRasterizerState(RHIRasterizerStateDefinition());
		GDepthStencilState = GDynamicRHI->RHICreateDepthStencilState(RHIDepthStencilStateDefinition());

	}
	bool Engine::ShouldExit()
	{
		return Input::OnWindowClosed();
	}

	void Engine::OnTick()
	{
		if (Input::OnWindowResized()) 
			GDynamicRHI->RHIResizeViewport(MainViewport.get(), MainWindow->GetWidth(), MainWindow->GetHeight(), false);
		
	}
	void Engine::OnDrawFrame()
	{
		GDynamicRHI->RHIBeginFrameViewport(MainViewport.get());
		GDynamicRHI->RHIEndFrameViewport(MainViewport.get());
	}
}