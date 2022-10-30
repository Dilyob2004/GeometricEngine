#include <Engine/Render/SwapChain.h>
#include <Engine/Render/Vulkan/VkSwapChain.h>
namespace MeteorEngine
{

	SwapChain* SwapChain::Create(RenderContext* context, const Vector2u& size, bool vsync)
	{
		return new VulkanSwapChain(dynamic_cast<VulkanContext*>(context), size, vsync);
	}
}