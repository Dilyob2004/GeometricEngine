#include <Editor/SceneHierarchy.h>
#include <Editor/Components.h>
#include <Engine/Math/MathUtils.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

namespace MeteorEngine
{

	void DrawElem3Controls(const std::string& name, Vector3f& values, float resetValues = 0.0f, float columnWidth = 100.f)
	{
		ImGui::PushID(name.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(name.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });

		if (ImGui::Button("X", buttonSize))
			values.x = resetValues;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValues;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.4784f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.61f, 0.99f, 1.0f });

		if (ImGui::Button("Z", buttonSize))
			values.z = resetValues;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();

	}
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


		bool opened = ImGui::TreeNodeEx((void*)(u64)(u32)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked()) 
		{
			m_selectionScene = entity;
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
		//Tag
		if(entity.HasComponent<Tag>())
		{
			auto& tag = entity.GetComponent<Tag>().tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);
		}

		//Transform
		if (entity.HasComponent<Transform>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{

				auto& transform = entity.GetComponent<Transform>();
				DrawElem3Controls("Position", transform.position);
				DrawElem3Controls("Rotation", transform.rotation);
				DrawElem3Controls("Scale", transform.scale, 1);
				ImGui::TreePop();
			}
		}

		//SpriteRenderer
		if (entity.HasComponent<SpriteRenderer>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer");
			
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
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
			ImGui::Begin("Hierarchy", &isActiveHierarchy);

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
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_selectionScene = {};

			ImGui::End();
		}
		if(isActiveProperties){
			ImGui::Begin("Properties", &isActiveProperties);

			if (m_selectionScene) {

				if (ImGui::Button("Add Component"))
					ImGui::OpenPopup("AddComponent");

				ImGui::SameLine();


				if (ImGui::BeginPopup("AddComponent"))
				{
					if (ImGui::MenuItem("Sprite Renderer"))
					{
						m_selectionScene.AddComponent<SpriteRenderer>();
					}
					if (ImGui::MenuItem("Transform"))
					{
						m_selectionScene.AddComponent<Transform>();
					}
					ImGui::EndPopup();
				}
				DrawComponentUI(m_selectionScene);
			}

			ImGui::End();
		}
	}
}