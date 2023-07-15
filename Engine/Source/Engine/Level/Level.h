#ifndef LEVEL_H
#define LEVEL_H

#include <Engine/Core/Misc/String.h>
#include <Engine/Renderer/Camera.h>
#include <Entt/entt.hpp>
class GEOMETRIC_API Actor;
class GEOMETRIC_API FLevel
{
public:
	FLevel();
	FLevel(const String&);
	~FLevel();
	Actor MakeActor(const String& Name);
	Actor MakeCameraActor();
	Actor MakeSquadActor();
	void RemoveActor(Actor);



	void OnDrawActors();

	
	void OnResize(const Vector2f& Size);
	void OnTick();

	void Serialize(const String& Path);
	void Deserialize(const String& Path);

	String GetName() const { return Name; }

	friend class Actor;

	entt::registry& GetHandleRegistry() { return HandleRegistry; }
	Camera GetMainCamera() { return MainCamera; }
private:
	String Name;
	entt::registry HandleRegistry;
	EditorCamera MainCamera;
};

#endif // !LEVEL_H
