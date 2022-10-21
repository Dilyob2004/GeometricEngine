#include <Engine/Render/RenderPass.h>
#include <Engine/Render/Vulkan/VkRenderPass.h>
namespace MeteorEngine
{

	RenderPass* RenderPass::Create(const RenderPassDesc& desc)
	{
		return new VulkanRenderPass(desc);
	}
}