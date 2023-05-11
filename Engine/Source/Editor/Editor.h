#ifndef EDITOR_H
#define EDITOR_H

#include <Engine/Core/Generic/Window.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
#include <Editor/SceneViewport.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Editor
	{
	public:
		static void InitializeProduct(const CHAR*);

		static TSharedPtr<Window>& GetMainWindow() { return MainWindow; }
		static TSharedPtr<RHIViewport>& GetMainViewport() { return MainViewport; }

		static void OnTick();
		static void OnFixedTick(){}
		static void OnLateTick(){}
		static void OnDrawFrame();
		static bool ShouldExit();
		static void OnExit(){}

	private:
		static TSharedPtr <Window> MainWindow;
		static TSharedPtr <RHIViewport> MainViewport;
		static TSharedPtr<SceneViewport> SceneRenderer;
	};
}


#endif