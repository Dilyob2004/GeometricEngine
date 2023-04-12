#ifndef ENGINE_H
#define ENGINE_H
#include <Engine/Core/Generic/Window.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Engine
	{
	public:
		static void InitializeProduct(const CHAR* );

		static TSharedPtr<Window>& GetMainWindow() { return MainWindow; }
		static TSharedPtr<RHIViewport>& GetMainViewport() { return MainViewport; }

		static void OnTick();
		static void OnFixedTick();
		static void OnLateTick();
		static void OnDrawFrame();
		static bool ShouldExit();
		static void OnExit();

	private:
		static TSharedPtr<Window> MainWindow;
		static TSharedPtr < RHIViewport> MainViewport;
	};
}
#endif // !ENGINE_H
