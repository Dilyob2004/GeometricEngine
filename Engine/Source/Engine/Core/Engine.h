#ifndef ENGINE_H
#define ENGINE_H
#include <Engine/Core/Generic/Window.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
#include <Engine/Level/Level.h>

class GEOMETRIC_API Engine
{
public:
	static void InitializeProduct(const CharAnsi* );

	static TScopePtr<Window>& GetMainWindow() { return MainWindow; }
	static RHIViewport* GetMainViewport() { return MainViewport; }

	static void OnTick();
	static void OnFixedTick(){}
	static void OnLateTick(){}
	static void OnDrawFrame();
	static bool ShouldExit();
	static void OnExit(){}

private:
	static TScopePtr<Window> MainWindow;
	static RHIViewport* MainViewport;
};
#endif // !ENGINE_H
