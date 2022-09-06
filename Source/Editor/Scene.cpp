
#include <Editor/Scene.h>
#include <Editor/Entity.h>
#include <Engine/Render/Renderer.h>
#include <Editor/Components.h>

namespace MeteorEngine
{

	Scene::Scene()
	{

	}
	Scene::~Scene()
	{

	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_registry.create(), this };
		entity.AddComponent<Transform>();

		auto &tag = entity.AddComponent<Tag>();
		tag.tag = name.empty() ? "New Entity" : name;
		if(tag.tag == "Square")
			entity.AddComponent<SpriteRenderer>();

		/**class Test : public ScriptLayer
		{
		public:
			Test() = default;
			virtual void OnUpdate()
			{
				LOG("xxxxx");
			}
		};
		entity.AddComponent<NativeScript>().Bind<Test>();*/
		return entity;
	}
	void Scene::DestroyEntity(Entity entity)
	{
		m_registry.destroy(entity);
	}
	void Scene::OnUpdate(float time)
	{
		{
			m_registry.view<NativeScript>().each([=](auto entity, auto & script) {
			
				if (!script.Instance)
				{
					script.InstantiateFunction();

				}
				script.UpdateFunction(script.Instance);
			
			});
		}

		{
			auto group = m_registry.group<Transform>(entt::get<SpriteRenderer>);
			for (auto entity : group)
			{
				auto [transform, spriteRenderer] = group.get<Transform, SpriteRenderer>(entity);
				RendererCommand::DrawQuad(transform.GetTransform(), spriteRenderer.color);
			}
		}
	}
}
