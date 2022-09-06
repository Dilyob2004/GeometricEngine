
#include <Editor/Entity.h>
namespace MeteorEngine
{
	Entity::Entity():
		m_entityHandle(entt::null),
		m_scene(NULL)
	{

	}
	Entity::Entity(entt::entity handle, Scene* scene):
		m_entityHandle(handle),
		m_scene(scene)
	{
	}
}
