
#include <Editor/Editor.h>
#include <Engine/Core/Application.h>
#include <Engine/Core/Input.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Math/MathUtils.h>
#include <Editor/Components.h>
#include <Engine/System/File.h>
#include <ImGui/imgui.h>
#include <ImGui/ImGuizmo.h>
#include <entt/entt.hpp>
#include <iostream>
namespace MeteorEngine
{


	bool isHovered = false, isOpenViewport = true;

	ImGuizmo::OPERATION typeGizmo = ImGuizmo::OPERATION::TRANSLATE;
    Editor::Editor():
        Layer("Editor"),
        m_cameraController(30, 1.778f, 0.1, 1000)
    {
		File* file = File::Open("Assets/Scene.scene", FileMode::CreateNew, FileAccess::ReadWrite, FileShare::ReadWrite);
		/////////////////////////////////////////////////////////////////////////
        FrameBufferSpecification spec;
        spec.size.x = Application::GetInstance().GetWindow().GetSize().x;
        spec.size.y = Application::GetInstance().GetWindow().GetSize().y;
        m_frameBuffer.reset(FrameBuffer::Create(spec));
		/////////////////////////////////////////////////////////////////////////
		
    }
    Editor::~Editor()
    {
    }


	void Editor::OnAttach()
	{

		m_console.reset(new Console());
		m_scene.reset(new Scene());
		m_scene->CreateEntity("Square");

		m_hierarchy.reset(new SceneHierarchy(m_scene));
		m_contentBrowser.reset(new ContentBrowser());

    }
    void Editor::OnDetach()
    {

    }


    void Editor::OnTick()
    {

		
        f32 time = m_clock.GetTime().GetSeconds();
        m_clock.Restart();


		if(isHovered)
			m_cameraController.OnUpdate(time);

		/////////////////////////////////////////////////////////////////////////
        m_frameBuffer->Bind();

            RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.f});
            RendererCommand::Clear();



            RendererCommand::SetupProjection3D(m_cameraController);
			m_scene->OnUpdate(time);

        m_frameBuffer->UnBind();
		/////////////////////////////////////////////////////////////////////////





		/////////////////////////////////////////////////////////////////////////
		if (isOpenViewport)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0 ,0 });
			ImGui::Begin("ViewPort", &isOpenViewport);
			if ((ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()))
				isHovered = true;

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if ((m_viewPortSize.x != viewportPanelSize.x || m_viewPortSize.y != viewportPanelSize.y))
			{

				m_frameBuffer->Resize({ (u32)viewportPanelSize.x, (u32)viewportPanelSize.y });
				m_viewPortSize = Vector2u((u32)viewportPanelSize.x, (u32)viewportPanelSize.y);
				m_cameraController.OnResize(m_viewPortSize);
			}
			ImGui::Image((ImTextureID)m_frameBuffer->GetColorAttachmentFrameBuffer(), { (f32)m_viewPortSize.x, (f32)m_viewPortSize.y }, ImVec2(0, 1), ImVec2(1, 0));



			if (m_hierarchy->GetSelectionEntity())
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();


				f32 windowW = (f32)ImGui::GetWindowWidth();
				f32 windowH = (f32)ImGui::GetWindowHeight();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowW, windowH);

				auto camera = m_cameraController;
				auto cameraProjection = camera.GetProjection();
				auto cameraView = camera.GetView();


				auto& transformComponent = m_hierarchy->GetSelectionEntity().GetComponent<Transform>();
				Matrix4f transform = transformComponent.GetTransform();

				ImGuizmo::Manipulate((f32*)& cameraView[0], (f32*)& cameraProjection[0], typeGizmo, ImGuizmo::LOCAL, (f32*)& transform[0]);
				if (ImGuizmo::IsUsing())
				{
					Vector3f position, rotation, scale{ 1, 1, 1 };
					DecomposeTransform(transform, position, rotation, scale);

					Vector3f deltaRotation = rotation - transformComponent.rotation;
					transformComponent.position = position;
					transformComponent.rotation = rotation;
					transformComponent.scale = scale;

				}
			}


			ImGui::End();
			ImGui::PopStyleVar();

		}
		/////////////////////////////////////////////////////////////////////////
		m_console->OnUpdate();
		m_hierarchy->OnUpdate();
		m_contentBrowser->OnUpdate();

    }
    void Editor::OnEvent(Event& e)
    {
		if(isHovered)
			m_cameraController.OnEvent(e);



		if (m_hierarchy->GetSelectionEntity())
		{
			switch (e.type)
			{
				case Event::KeyPressed:
				{
					if (e.keyEvent.code == KeyCode::LAlt) {
						if (e.keyEvent.code == KeyCode::Q) typeGizmo = ImGuizmo::OPERATION::TRANSLATE;
						if (e.keyEvent.code == KeyCode::W) typeGizmo = ImGuizmo::OPERATION::ROTATE;
						if (e.keyEvent.code == KeyCode::E) typeGizmo = ImGuizmo::OPERATION::SCALE;
					}
				}
				break;
			}
		}
    }

	void Editor::SetViewPort(bool active)
	{
		isOpenViewport = active;

	}
	void Editor::SetSceneHierarchy(bool active)
	{
		SceneHierarchy::SetActiveHierarchy(active);
	}

	void Editor::SetProperties(bool active)
	{
		SceneHierarchy::SetActiveProperties(active);
	}
	void Editor::SetContentBrowser(bool active)
	{
		ContentBrowser::SetActive(active);
	}
	void Editor::SetConsole(bool active)
	{
		Console::SetActive(active);
	}
}