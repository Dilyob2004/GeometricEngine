#ifndef EditorViewport_H
#define EditorViewport_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
#include <Engine/Math/Vector2.h>
#include <Engine/Level/Level.h>

class GEOMETRIC_API EditorViewport
{
public:
	EditorViewport();
	~EditorViewport();


	void OnPaint();
	void OnRenderer();
	void OnTick();

	FLevel* GetActiveLevel() { return Level; }
private:


	RHIRenderTarget* RenderTarget;
	Vector2f ViewSize{1280, 720};
	FLevel* Level;
	bool HasFocus;
	bool IsOpen;

};

#endif // !EditorViewport_H
