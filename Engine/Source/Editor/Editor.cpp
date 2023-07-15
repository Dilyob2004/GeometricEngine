#include "Editor.h"

#include <Engine/Core/Misc/Log.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/ImageCore/ImageCore.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <ImGui/imgui.h>

TScopePtr < Window> Editor::MainWindow;
RHIViewport* Editor::MainViewport = NULL;
EditorViewport* Editor::EditorView = NULL;
PropertyEditor* Editor::Property = NULL;
OutlinerEditor* Editor::Outliner = NULL;
ContentBrowserEditor* Editor::ContentBrowser = NULL;


void Editor::InitializeProduct(const CharAnsi* CmdLine)
{
	if (!InitializeDynamicRHI())
	{
		LOG("Error:[RHI] Failed to Initizlied!\n");
		exit(-1);
	}
	LOG("Info: [DYNAMICRHI] Initialized!\n");
	ShaderCompileWorker::DefaultInitialize();

	WindowDefinition Info;
	Info.Title = ("GeometricEditor");
	Info.SizeWidth = 1280;
	Info.SizeHeight = 720;
	Info.Fullscreen = false;
	MainWindow.reset(Window::Create(Info));

	RHIViewportDefinition Definition;
	Definition.Width = MainWindow->GetWidth();
	Definition.Height = MainWindow->GetHeight();
	Definition.HandleWindow = MainWindow->GetHandle();
	Definition.FullScreen = Info.Fullscreen;
	MainViewport = GDynamicRHI->RHICreateViewport(Definition),
					GDynamicRHI->RHICreateGUI(MainWindow->GetHandle());

	EditorView = new EditorViewport();
	Property = new PropertyEditor();
	Outliner = new OutlinerEditor(EditorView->GetActiveLevel());
	ContentBrowser = new ContentBrowserEditor();
		
}
bool Editor::ShouldExit()
{
	return Input::OnWindowClosed();
}

void Editor::OnTick()
{
	if (Input::OnWindowResized())
		GDynamicRHI->RHIResizeViewport(MainViewport, MainWindow->GetWidth(), MainWindow->GetHeight(), false);

	
	EditorView->OnTick();
}
void Editor::OnDrawFrame()
{

	EditorView->OnRenderer();


	GDynamicRHI->RHIBeginFrameViewport(MainViewport);

		GDynamicRHI->RHIBeginFrameGUI();

			EditorView->OnPaint();
			Property->OnPaint();
			Outliner->OnPaint();
			ContentBrowser->OnPaint();

		GDynamicRHI->RHIEndFrameGUI();

	GDynamicRHI->RHIEndFrameViewport(MainViewport);

}
