#ifndef OUTLINEREDITOR_H
#define OUTLINEREDITOR_H
#include <Engine/Level/Level.h>

class GEOMETRIC_API OutlinerEditor
{
public:
	OutlinerEditor();
	OutlinerEditor(FLevel*);

	void SetStreamingLevel(FLevel* NewLevel) { StreamingLevel = NewLevel; }
	void OnPaint();
private:
	void OnDrawActorOutliner(Actor);


private:
	FLevel* StreamingLevel;
	bool IsOpen;
};
#endif // !OUTLINEREDITOR_H
