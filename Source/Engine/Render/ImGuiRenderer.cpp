#include <Engine/Render/ImGuiRenderer.h>
#include <Engine/Render/Vulkan/VkImGuiRenderer.h>


namespace MeteorEngine
{

	ImGuiRenderer* ImGuiRenderer::Create(const Vector2u& size, bool clear)
	{
		return new VulkanImGuiRenderer(size, clear);
	}
}