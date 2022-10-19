#include <Engine/Render/RenderContext.h>
#include <Engine/Render/Vulkan/VkContext.h>
namespace MeteorEngine
{
	RenderContext* RenderContext::Create(Window* window)
    {
         return new VulkanContext(window);
    }
}
