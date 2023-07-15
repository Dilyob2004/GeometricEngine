#include "Actor.h"

Actor::Actor()
	: CurrentLevel(NULL)
	, EntityHandle(entt::null)
{
}
Actor::Actor(entt::entity Entity, FLevel* NewLevel)
	: CurrentLevel(NewLevel)
	, EntityHandle(Entity)
{
}
