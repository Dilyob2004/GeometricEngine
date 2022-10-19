#include <Engine/Render/Renderer.h>
#include <Engine/Render/Vulkan/VkRenderer.h>
namespace MeteorEngine
{
	Renderer* RendererCommand::m_Renderer = new VulkanRenderer();
	void RendererCommand::Init(RenderContext* context, const Vector2u& size, bool vsync)
	{
		m_Renderer->Init(context, size, vsync);
	}
	void RendererCommand::Begin()
	{
		m_Renderer->Begin();
	}
	void RendererCommand::Present()
	{
		m_Renderer->Present();
	}
	void RendererCommand::Resize(const Vector2u& size)
	{
		m_Renderer->Resize(size);
	}
}
