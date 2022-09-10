#include "ExampleLayer.h"
#include "../Engine/Render/Renderer.h"
#include "../Engine/Math/Matrix4.h"
#include "../Engine/Core/Input.h"
#include "../Engine/Core/Application.h"
namespace MeteorEngine
{
    ExampleLayer::ExampleLayer():
        Layer("ExampleLayer")
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
	void DrawBoxUI(const Vector2u& size, const Vector2i& position, const Vector4u& color)
	{
		Vector2f newSize = Vector2f((f32)size.x / (f32)Application::GetInstance().GetWidth(), (f32)size.y / (f32)Application::GetInstance().GetHeight());
		Vector2f newPosition = Vector2f((f32)position.x / (f32)Application::GetInstance().GetWidth(), (f32)position.y / (f32)Application::GetInstance().GetHeight());
		Vector4f newColor = Vector4f((f32)color.x / 255, (f32)color.y / 255, (f32)color.z / 255, (f32)color.w / 255);

		RendererCommand::DrawQuad2D(newPosition, { 0, 0}, newSize, newColor);

	}
    void ExampleLayer::OnTick()
    {

		
		RendererCommand::SetupProjection2D(Camera2D(-1, 1, -1, 1) );
		//DrawBoxUI({ 100, 23 }, { -100, 200-23, }, { 36, 36, 36, 255 });
		DrawBoxUI({ 200, 200 }, { 0, 0, }, { 255,255,255, 255 });


		//DrawBoxUI({ 200, 200 }, { 0, 0 }, {255, 255, 255, 255});
    }
    void ExampleLayer::OnEvent(Event& e)
    {

    }
}

