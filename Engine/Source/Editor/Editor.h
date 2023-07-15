#ifndef EDITOR_H
#define EDITOR_H

#include <Engine/Core/Generic/Window.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
#include "EditorViewport.h"
#include "PropertyEditor.h"
#include "OutlinerEditor.h"
#include "ContentBrowserEditor.h"

class GEOMETRIC_API Editor
{
public:
	static void InitializeProduct(const CharAnsi* );

	static Window* GetMainWindow() { return MainWindow.get(); }
	static RHIViewport* GetMainViewport() { return MainViewport; }

	static EditorViewport* GetEditorView() { return EditorView; }
	static PropertyEditor* GetProperty() { return Property; }
	static OutlinerEditor* GetOutliner() { return Outliner; }

	static void OnTick();
	static void OnFixedTick(){}
	static void OnLateTick(){}
	static void OnDrawFrame();
	static bool ShouldExit();
	static void OnExit(){}

private:
	static TScopePtr< Window> MainWindow;
	static RHIViewport* MainViewport;

	static EditorViewport* EditorView;
	static PropertyEditor* Property;
	static OutlinerEditor* Outliner;
	static ContentBrowserEditor* ContentBrowser;
};

#endif