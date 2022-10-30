#include <Engine/Render/UniformBuffer.h>
#include <Engine/Render/Vulkan/VkUniformBuffer.h>


namespace MeteorEngine
{
	UniformBuffer* UniformBuffer::Create(cp0* uniforms, u32 size)
	{
		return new VulkanUniformBuffer(uniforms, size);
	}

}