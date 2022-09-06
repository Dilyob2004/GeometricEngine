#ifndef ENTITY_H
#define ENTITY_H
#include <Editor/Scene.h>
#include <entt/entt.hpp>
namespace MeteorEngine
{

	class METEOR_API Entity
	{
	public:
		Entity();
		Entity(entt::entity, Scene*);
		Entity(const Entity&) = default;

		template<typename T, typename ...Args>
		T& AddComponent(Args&&... args)
		{
			return m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_scene->m_registry.remove<T>(m_entityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_scene->m_registry.get<T>(m_entityHandle);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.any_of<T>(m_entityHandle);
		}
		Scene* GetScene() const { return m_scene;  }

		operator bool() const { return m_entityHandle != entt::null; }
		operator entt::entity() const { return m_entityHandle; }
		operator u32() const { return (u32)m_entityHandle; }

		bool operator == (const Entity& other) const { return m_entityHandle == other.m_entityHandle && m_scene == other.m_scene; }
		bool operator != (const Entity& other) const { return !(*this == other); }

	private:
		Scene*			m_scene;
		entt::entity	m_entityHandle{entt::null};
	};
}

#endif // ENTITY_H
