#include "OutlinerEditor.h"
#include "Editor.h"
#include <Engine/Level/Actor.h>
#include <Engine/Level/ActorComponents.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

OutlinerEditor::OutlinerEditor()
	: IsOpen(true)
	, StreamingLevel(NULL)
{
}
OutlinerEditor::OutlinerEditor(FLevel* NewLevel)
	: IsOpen(true)
{
	SetStreamingLevel(NewLevel);
}

void OutlinerEditor::OnPaint()
{
	ImGui::Begin("Outliner", &IsOpen);

	if (ImGui::BeginPopupContextWindow(NULL, ImGuiPopupFlags_MouseButtonRight))
	{
		if (ImGui::MenuItem("Camera"))
			StreamingLevel->MakeCameraActor();


		if (ImGui::MenuItem("Square"))
			StreamingLevel->MakeSquadActor();


		ImGui::EndPopup();
	}

	StreamingLevel->GetHandleRegistry().each([&](auto entity)
	{
		Actor NewActor(entity, StreamingLevel);
		OnDrawActorOutliner(NewActor);
	});


	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		(Editor::GetProperty())->SetSelectionActor({});

	ImGui::End();
}
void OutlinerEditor::OnDrawActorOutliner(Actor StreamedActor)
{

	ImGuiTreeNodeFlags flags = (Editor::GetProperty()->GetSelectionActor() == StreamedActor) ? ImGuiTreeNodeFlags_Selected : 0 | ImGuiTreeNodeFlags_OpenOnArrow;
	flags |= ImGuiTreeNodeFlags_Leaf;

	bool Opened = ImGui::TreeNodeEx((void*)(U64)(U32)StreamedActor, flags, *StreamedActor.GetComponent<NameComponent>().Name);

	if (ImGui::IsItemClicked())
		Editor::GetProperty()->SetSelectionActor(StreamedActor);
		
	bool ActorDestroyed = false;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete Entity"))
			ActorDestroyed = true;

		ImGui::EndPopup();
	}
	if (Opened)
		ImGui::TreePop();


	if (ActorDestroyed)
	{
		StreamingLevel->RemoveActor(StreamedActor);
		if (Editor::GetProperty()->GetSelectionActor() == StreamedActor)
			Editor::GetProperty()->SetSelectionActor({ });
	}
}
