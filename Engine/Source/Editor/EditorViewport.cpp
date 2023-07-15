#include "EditorViewport.h"

#include <Engine/ImageCore/ImageCore.h>
#include <Engine/InputCore/InputCore.h>
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Renderer/Renderer2D.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/Level/Actor.h>
#include <Engine/Level/ActorComponents.h>
#include <Engine/Core/Misc/Log.h>
#include "Editor.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <ImGui/ImGuizmo.h>

void Draw2DGrid(ImDrawList* drawList,
	const ImVec2& cameraPos,
	const ImVec2& windowPos,
	const ImVec2& canvasSize,
	const float factor,
	const float thickness)
{
	static const auto graduation = 10;
	float GRID_SZ = canvasSize.y * 0.5f / factor;
	const ImVec2& offset = {
		canvasSize.x * 0.5f - cameraPos.x * GRID_SZ, canvasSize.y * 0.5f + cameraPos.y * GRID_SZ
	};

	ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
	float gridThickness = 1.0f;

	const auto& gridColor = GRID_COLOR;
	auto smallGraduation = GRID_SZ / graduation;
	const auto& smallGridColor = IM_COL32(100, 100, 100, smallGraduation);

	for (float x = -GRID_SZ; x < canvasSize.x + GRID_SZ; x += GRID_SZ)
	{
		auto localX = floorf(x + fmodf(offset.x, GRID_SZ));
		drawList->AddLine(
			ImVec2{ localX, 0.0f } + windowPos, ImVec2{ localX, canvasSize.y } + windowPos, gridColor, gridThickness);

		if (smallGraduation > 5.0f)
		{
			for (int i = 1; i < graduation; ++i)
			{
				const auto graduation = floorf(localX + smallGraduation * i);
				drawList->AddLine(ImVec2{ graduation, 0.0f } + windowPos,
					ImVec2{ graduation, canvasSize.y } + windowPos,
					smallGridColor,
					1.0f);
			}
		}
	}

	for (float y = -GRID_SZ; y < canvasSize.y + GRID_SZ; y += GRID_SZ)
	{
		auto localY = floorf(y + fmodf(offset.y, GRID_SZ));
		drawList->AddLine(
			ImVec2{ 0.0f, localY } + windowPos, ImVec2{ canvasSize.x, localY } + windowPos, gridColor, gridThickness);

		if (smallGraduation > 5.0f)
		{
			for (int i = 1; i < graduation; ++i)
			{
				const auto graduation = floorf(localY + smallGraduation * i);
				drawList->AddLine(ImVec2{ 0.0f, graduation } + windowPos,
					ImVec2{ canvasSize.x, graduation } + windowPos,
					smallGridColor,
					1.0f);
			}
		}
	}
}
ImGuizmo::OPERATION typeGizmo = ImGuizmo::OPERATION::TRANSLATE;
EditorViewport::EditorViewport()
{
	HasFocus = true;
	IsOpen = true;

	RHITextureDefinition TextureDef;
	TextureDef.Width = ViewSize.x;
	TextureDef.Height = ViewSize.y;
	TextureDef.Format = RHIPixelFormat::R8G8BA8_UNORM;
	RenderTarget = GDynamicRHI->RHICreateRenderTarget(TextureDef);


	Renderer2D::Init();
	Level = new FLevel("DefaultLevel");
}
EditorViewport::~EditorViewport()
{
	RenderTarget->SafeRelease();
}
void EditorViewport::OnTick()	
{

	if (HasFocus)
		Level->OnTick();

}
void EditorViewport::OnRenderer()
{
	GDynamicRHI->RHISetRenderTarget(RenderTarget);
	GDynamicRHI->RHIClearRenderTarget(RenderTarget, 30, 30, 30, 30);
	Level->OnDrawActors();


}
void EditorViewport::OnPaint()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0 ,0 });
	ImGui::Begin("Viewport", &IsOpen);
		HasFocus = ImGui::IsWindowFocused();

		ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
		if (ViewSize.x != ViewportPanelSize.x || ViewSize.y != ViewportPanelSize.y)
		{
			ViewSize.x = ViewportPanelSize.x;
			ViewSize.y = ViewportPanelSize.y;
			GDynamicRHI->RHIResizeRenderTarget(&RenderTarget, (U32)ViewSize.x, (U32)ViewSize.y);
			Level->OnResize(ViewSize);
		}
		ImGui::Image(RenderTarget->GetHandle(), { ViewSize.x, ViewSize.y });

		//ImVec2 ViewportGrid{ ViewportPanelSize.x * SceneCamera.GetViewSize().x, ViewportPanelSize.y * SceneCamera.GetViewSize().y };
		//Draw2DGrid(ImGui::GetWindowDrawList(), { SceneCamera.GetPosition().x, SceneCamera.GetPosition().y }, ImGui::GetWindowPos(), ViewportGrid, 5, 1.1f);
		if (Editor::GetProperty()->GetSelectionActor())
		{
			ImGuizmo::SetOrthographic(true);
			ImGuizmo::SetDrawlist();


			F32 windowW = (F32)ImGui::GetWindowWidth();
			F32 windowH = (F32)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowW, windowH);

			auto cameraProjection = Level->GetMainCamera().GetProjection();
			auto cameraView = Level->GetMainCamera().GetView();


			auto& transformComponent = Editor::GetProperty()->GetSelectionActor().GetComponent<Transform2DComponent>();
				
				
			//FMatrix4 transform = transformComponent.GetTransform();
			struct 
			{
				FMatrix4 GetTransform()
				{
					return MathUtils::Translate(FMatrix4::Identity, Position)* MathUtils::QuaternionToMatrix4(FQuaternion(Rotation)) * MathUtils::Scale(FMatrix4::Identity, Scale);
				}
				Vector3f Position;
				Vector3f Rotation;
				Vector3f Scale;
			}TransformImGui;
				
			TransformImGui.Position = Vector3f(transformComponent.Position.x, transformComponent.Position.y, 0.0f);
			TransformImGui.Rotation = Vector3f(0.0f, 0.0f, transformComponent.Rotation);
			TransformImGui.Scale = Vector3f(transformComponent.Scale.x, transformComponent.Scale.y, 1.0f);

			FMatrix4 transform = TransformImGui.GetTransform();
				
			//ImGuizmo::DrawGrid((F32*)&cameraView[0], (F32*)&cameraProjection[0], (F32*)&FMatrix4::Identity[0], 100.f);
			ImGuizmo::Manipulate((F32*)&cameraView[0], (F32*)&cameraProjection[0], typeGizmo, ImGuizmo::LOCAL, (F32*)&transform[0]);
				
			if (ImGuizmo::IsUsing())
			{
				Vector3f Position, Rotation, Scale{ 1, 1, 1 };
				MathUtils::DecomposeTransform(transform, Position, Rotation, Scale);

				//Vector3f deltaRotation = rotation - transformComponent.rotation;
				transformComponent.Position = { Position.x, Position.y };
				transformComponent.Rotation = Rotation.z;
				transformComponent.Scale = { Scale.x, Scale.y };

			}
			/*if (e.keyEvent.code == KeyCode::LAlt) {
				if (e.keyEvent.code == KeyCode::Q) typeGizmo = ImGuizmo::OPERATION::TRANSLATE;
				if (e.keyEvent.code == KeyCode::W) typeGizmo = ImGuizmo::OPERATION::ROTATE;
				if (e.keyEvent.code == KeyCode::E) typeGizmo = ImGuizmo::OPERATION::SCALE;
			}*/
		}
				
	ImGui::End();
	ImGui::PopStyleVar();


}