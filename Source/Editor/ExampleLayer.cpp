#include "ExampleLayer.h"
#include "../Engine/Render/Renderer.h"
#include "../Engine/Math/Matrix4.h"
#include "../Engine/Core/Input.h"
#include "../ThirdParty/ImGui/imgui.h"
#include "../Engine/Core/Application.h"
namespace MeteorEngine
{
    ExampleLayer::ExampleLayer():
        Layer("ExampleLayer"),
		m_cameraController(1)
    {
    }
    ExampleLayer::~ExampleLayer()
    {

    }
    void ExampleLayer::OnAttach()
    {

    }
    void ExampleLayer::OnDetach()
    {

    }
	void DrawBox(const Vector2f& size, const Vector2f& position, const Vector4f& color)
	{
		RendererCommand::DrawQuad({ position.x, position.y, 0 }, { 0, 0, 0 }, { size.x, size.y, 0 }, color, true);

	}
	void DrawBoxUI(const Vector2u& size, const Vector2i& position, const Vector4f& color)
	{
		Vector2f newSize = Vector2f((f32)size.x / Application::GetInstance().GetWidth(), (f32)size.y / Application::GetInstance().GetHeight());
		Vector2f newPosition = Vector2f((f32)position.x / Application::GetInstance().GetWidth(), (f32)position.y / Application::GetInstance().GetHeight());
		Vector4f newColor = Vector4f((f32)color.x / 255, (f32)color.y / 255, (f32)color.z / 255, (f32)color.w / 255);

		RendererCommand::DrawQuad({ newPosition.x, newPosition.y, 0 }, { 0, 0, 0 }, { newSize.x, newSize.y, 0 }, newColor, true);

	}
    void ExampleLayer::OnUpdate()
    {
		f32 time = m_clock.GetTime().GetSeconds();
		m_clock.Restart();
		m_cameraController.OnUpdate(time);

		
		RendererCommand::SetCamera(m_cameraController.GetCamera());
		DrawBoxUI({ 100, 23 }, { -100, 200-23, }, { 36, 36, 36, 255 });
		DrawBoxUI({ 200, 200 }, { 0, 0, }, { 21,21,21, 255 });
    }
    void ExampleLayer::OnEvent(Event& e)
    {
    }
}

