#include "PropertyEditor.h"
#include "Engine/Level/ActorComponents.h"
#include <Engine/SlateCore/SlateUtilities.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
PropertyEditor::PropertyEditor()
	: SelectionActor()
	, IsOpen(true)
{

}
void PropertyEditor::OnPaint()
{
	ImGui::Begin("Property", &IsOpen);
	if (SelectionActor)
	{

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		ImGui::SameLine();


		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Sprite Renderer"))
				SelectionActor.AddComponent<SpriteRendererComponent>();

			if (ImGui::MenuItem("Transform"))
				SelectionActor.AddComponent<Transform2DComponent>();

			ImGui::EndPopup();
		}
		OnDrawComponents(SelectionActor);
	}
	ImGui::End();
}
void PropertyEditor::OnDrawComponents(Actor StreamedActor)
{

	//Tag
	if (StreamedActor.HasComponent<NameComponent>())
	{
		auto& Tag = StreamedActor.GetComponent<NameComponent>().Name;
		CharAnsi Buffer[256];
		SMemory::Set(Buffer, sizeof(Buffer), 0);
		CString::Copy(Buffer, Tag.Pointer());
		if (ImGui::InputText("Tag", Buffer, sizeof(Buffer))) {
			if(Buffer != NULL)
				Tag = String(Buffer);
		}
	}




	//Transform
	if (StreamedActor.HasComponent<Transform2DComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(Transform2DComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{

			auto& Transform = StreamedActor.GetComponent<Transform2DComponent>();
			SlateUtilities::DrawElem2Controls("Position", Transform.Position);
			SlateUtilities::DrawElem1Controls("Rotation", Transform.Rotation);
			SlateUtilities::DrawElem2Controls("Scale",	  Transform.Scale, 1);

			ImGui::TreePop();
		}
	}

	//SpriteRenderer
	if (StreamedActor.HasComponent<SpriteRendererComponent>())
	{
		bool Open = ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer");

		if (ImGui::IsItemFocused() && ImGui::IsMouseClicked(1))
			ImGui::OpenPopup("Settings");
			

		bool RemoveComponent = false;
		if (ImGui::BeginPopup("Settings"))
		{
			if (ImGui::MenuItem("Remove"))
				RemoveComponent = true;

			ImGui::EndPopup();
		}
		if (Open)
		{
			auto& SpriteRenderer = StreamedActor.GetComponent<SpriteRendererComponent>();
			ImGui::ColorEdit4("Color", &SpriteRenderer.Color[0]);
			ImGui::TreePop();

		}
		if (RemoveComponent)
			StreamedActor.RemoveComponent<SpriteRendererComponent>();
	}
}