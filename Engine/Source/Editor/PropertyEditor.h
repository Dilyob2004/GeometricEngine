#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H
#include <Engine/Level/Level.h>
#include <Engine/Level/Actor.h>

class GEOMETRIC_API PropertyEditor
{
public:
	PropertyEditor();
	void OnPaint();
	Actor GetSelectionActor() { return SelectionActor; }
	void SetSelectionActor(Actor NewActor) { SelectionActor = NewActor; }
private:
	void OnDrawComponents(Actor);


private:
	Actor	SelectionActor;

	bool IsOpen;
};
#endif // !
