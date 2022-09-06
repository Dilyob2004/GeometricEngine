#ifndef SCENE_H
#define SCENE_H

#include <Engine/Core/Config.h>
#include <entt/entt.hpp>
namespace MeteorEngine
{
	class METEOR_API Entity;
    class METEOR_API Scene
    {
    public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string&);
		void DestroyEntity(Entity);

		entt::registry& GetRegistry() { return m_registry; }

		void OnUpdate(float);
		friend class Entity;

	private:

		entt::registry m_registry{};

    };
}
#endif // SCENE_H
