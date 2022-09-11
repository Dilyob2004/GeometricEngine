#include "ExampleLayer.h"
#include "../Engine/Render/Renderer.h"
#include "../Engine/Math/Matrix4.h"
#include "../Engine/Core/Input.h"
#include "../Engine/Core/Application.h"
#include <Engine/Render/Texture.h>
namespace MeteorEngine
{

	std::shared_ptr<Texture2D> texture;
    ExampleLayer::ExampleLayer():
        Layer("ExampleLayer")
    {
		texture.reset(Texture2D::Create("Assets/Texture/logo.png")) ;
    }
    ExampleLayer::~ExampleLayer()
    {

    }
    void ExampleLayer::OnAttach()
    {
		f32 L = (f32)Application::GetInstance().GetX();
		f32 R = (f32)Application::GetInstance().GetX() + Application::GetInstance().GetWidth();
		f32 T = (f32)Application::GetInstance().GetY();
		f32 B = (f32)Application::GetInstance().GetY() + Application::GetInstance().GetHeight();
		Camera2D ortho(-1, 1, 1, -1);

		ortho.SetPosition({ 0, 0, 0 });
		ortho.SetRotation(0);
		RendererCommand::SetupProjection2D(ortho);
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
	void DrawTextureUI(const std::shared_ptr<Texture2D>& textureUI, const Vector2u& size, const Vector2i& position)
	{
		Vector2f newSize = Vector2f((f32)size.x / (f32)Application::GetInstance().GetWidth(), (f32)size.y / (f32)Application::GetInstance().GetHeight());
		Vector2f newPosition = Vector2f((f32)position.x / (f32)Application::GetInstance().GetWidth(), (f32)position.y / (f32)Application::GetInstance().GetHeight());

		RendererCommand::DrawTextureQuad(texture, { newPosition.x,  newPosition.y, 0 }, { 0, 0, 0 }, { newSize.x, newSize .y});

	}
    void ExampleLayer::OnTick()
    {

		
		//DrawBoxUI({ 100, 23 }, { -100, 200-23, }, { 36, 36, 36, 255 });
		//DrawBoxUI({ 200, 200 }, { 0, 0, }, { 255,255,255, 255 });
		//RendererCommand::DrawTextureQuad(texture, { 0, 0, 0 }, {0.5f, 0.5f});
		//RendererCommand::DrawTextureQuad();

		//RendererCommand::DrawTextureQuad(texture, { 0,  0, 0 }, { 0, 0, 0 }, {0.5, 0.5});

		DrawTextureUI(texture, { 96, 96 }, { -(s32)Application::GetInstance().GetWidth(), (s32)Application::GetInstance().GetHeight() -100});

		//DrawBoxUI({ 200, 200 }, { 0, 0 }, {255, 255, 255, 255});
    }
    void ExampleLayer::OnEvent(Event& e)
    {

    }
}

