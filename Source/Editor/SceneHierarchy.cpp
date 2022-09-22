#include <Editor/SceneHierarchy.h>
#include <Editor/Components.h>
#include <Engine/Math/MathUtils.h>
#include <Engine/Gui/ImGuiLayer.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <Engine/IconsMaterialDesignIcons.h>

namespace MeteorEngine
{
	static bool isActiveProperties = true, isActiveHierarchy = true;
	void SceneHierarchy::SetActiveProperties(bool active)
	{
		isActiveProperties = active;
	}
	void SceneHierarchy::SetActiveHierarchy(bool active)
	{
		isActiveHierarchy = active;
	}
	SceneHierarchy::SceneHierarchy() 
	{

	}
	SceneHierarchy::SceneHierarchy(const std::shared_ptr<Scene>& scene) 
	{
		SetScene(scene);
	}

	SceneHierarchy::~SceneHierarchy()
	{

	}
	void SceneHierarchy::SetScene(const std::shared_ptr<Scene>& scene)
	{
		m_scene = scene;
	}
	void SceneHierarchy::DrawEntity(Entity entity)
	{
		auto& tag = entity.GetComponent<Tag>().tag;
		ImGuiTreeNodeFlags flags = (m_selectionScene == entity) ? ImGuiTreeNodeFlags_Selected : 0 | ImGuiTreeNodeFlags_OpenOnArrow;
		if(1)
			flags |= ImGuiTreeNodeFlags_Leaf;

		
		std::string icon = ICON_MDI_CUBE_OUTLINE;
		bool opened = ImGui::TreeNodeEx((void*)(u64)(u32)entity, flags, "%s  %s", icon.c_str(),tag.c_str());
		{
			if (ImGui::IsItemClicked())
			{
				m_selectionScene = entity;
			}
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_selectionScene = {};
		}
		
		if (ImGui::IsMouseDoubleClicked(0))
		{
			ImGui::PushItemWidth(-1);
			auto& tag = entity.GetComponent<Tag>().tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);

		}
		bool entityDestroyed = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity")) 
				entityDestroyed = true;

			ImGui::EndPopup();
		}
		if (opened)
			ImGui::TreePop();


		if (entityDestroyed)
		{
			m_scene->DestroyEntity(entity);
			if (m_selectionScene == entity)
				m_selectionScene = {};
		}

	}
	void SceneHierarchy::DrawComponentUI(Entity entity)
	{
		ImGui::Separator();

		//Tag
		if(entity.HasComponent<Tag>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Tag).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, ICON_MDI_TAG "Tag"))
			{
				auto& tag = entity.GetComponent<Tag>().tag;
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());
				if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
					tag = std::string(buffer);

				ImGui::TreePop();
			}
		}
		ImGui::Separator();

		//Transform
		if (entity.HasComponent<Transform>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, ICON_MDI_VECTOR_LINE " Transform"))
			{

				auto& transform = entity.GetComponent<Transform>();
				ImGuiLayer::DrawElem3Controls("Position", transform.position);
				ImGuiLayer::DrawElem3Controls("Rotation", transform.rotation);
				ImGuiLayer::DrawElem3Controls("Scale", transform.scale, 1);
				ImGui::TreePop();
			}
		}
		ImGui::Separator();

		//SpriteRenderer
		if (entity.HasComponent<SpriteRenderer>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, ICON_MDI_IMAGE " Sprite Renderer");

			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+"))
			{
				ImGui::OpenPopup("Settings");
			}
			ImGui::PopStyleVar();


			bool removecomponent = false;
			if (ImGui::BeginPopup("Settings"))
			{
				if (ImGui::MenuItem("Remove"))
					removecomponent = true;
				ImGui::EndPopup();
			}
			if (open)
			{
				auto& spriteRenderer = entity.GetComponent<SpriteRenderer>();
				ImGui::ColorEdit4("Color", &spriteRenderer.color[0]);
				ImGui::TreePop();

			}
			if (removecomponent)
				entity.RemoveComponent<SpriteRenderer>();
		}

	}
	void SceneHierarchy::OnUpdate()
	{


		if (isActiveHierarchy) {
			ImGui::Begin(ICON_MDI_VIEW_LIST " Hierarchy", &isActiveHierarchy);

			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Square")) {
					m_scene->CreateEntity("Square");
				}
				ImGui::EndPopup();
			}

			m_scene->GetRegistry().each([&](auto entity)
			{
				Entity newEntity{ entity , m_scene.get() };
				DrawEntity(newEntity);
			});

			ImGui::End();
		}
		if(isActiveProperties)
		{
			ImGui::Begin(ICON_MDI_INFORMATION " Properties", &isActiveProperties);

			if (m_selectionScene) {

				if (ImGui::Button("Add Component"))
					ImGui::OpenPopup("AddComponent");



				if (ImGui::BeginPopup("AddComponent"))
				{
					if (ImGui::MenuItem("Sprite Renderer") && !m_selectionScene.HasComponent<SpriteRenderer>())
					{
						m_selectionScene.AddComponent<SpriteRenderer>();
					}
					ImGui::EndPopup();
				}
				DrawComponentUI(m_selectionScene);
			}

			ImGui::End();
		}
	}
}