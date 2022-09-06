#ifndef  SCENEHIERARCHY_H
#define SCENEHIERARCHY_H
#include <Engine/Core/Config.h>
#include <Editor/Scene.h>
#include <Editor/Entity.h>
#include <memory>
namespace MeteorEngine
{
	class METEOR_API SceneHierarchy
	{
	public:
		SceneHierarchy();
		SceneHierarchy(const std::shared_ptr<Scene>&);
		~SceneHierarchy();
		void SetScene(const std::shared_ptr<Scene>&);
		void OnUpdate();

		void DrawEntity(Entity);
		void DrawComponentUI(Entity);

		Entity GetSelectionEntity() const { return m_selectionScene;  }
		static void SetActiveHierarchy(bool);
		static void SetActiveProperties(bool);
	private:
		std::shared_ptr<Scene>	m_scene;
		Entity					m_selectionScene;
	};
}
#endif // ! SCENEHIERARCHY_H
