#ifndef ACTOR_H
#define ACTOR_H


#include <Engine/Core/Config.h>
#include "Level.h"

class GEOMETRIC_API Actor
{
public:
	Actor();
	Actor(entt::entity, FLevel* );
	Actor(const Actor&) = default;

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		return CurrentLevel->HandleRegistry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
	}
		
	template<typename T>
	T& GetComponent()
	{
		return CurrentLevel->HandleRegistry.get<T>(EntityHandle);
	}

	template<typename T>
	bool HasComponent()
	{
		return CurrentLevel->HandleRegistry.any_of<T>(EntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		CurrentLevel->HandleRegistry.remove<T>(EntityHandle);
	}

	FLevel* GetCurrentLevel() const { return CurrentLevel; }

	operator bool() const { return EntityHandle != entt::null; }
	operator entt::entity() const { return EntityHandle; }
	operator U32() const { return (U32)EntityHandle; }

	bool operator == (const Actor& Other) const { return EntityHandle == Other.EntityHandle; }
	bool operator != (const Actor& Other) const { return !(*this == Other); }


private:
	FLevel* CurrentLevel;
	entt::entity EntityHandle;
};
#endif // !ACTOR_H
