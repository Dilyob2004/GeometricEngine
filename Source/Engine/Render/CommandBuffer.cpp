#include <Engine/Render/CommandBuffer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>

namespace MeteorEngine {

	CommandBuffer* CommandBuffer::Create()
	{
		return new VulkanCommandBuffer();
	}
}