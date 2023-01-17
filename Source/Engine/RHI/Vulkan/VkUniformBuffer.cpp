#include <Engine/Render/Vulkan/VkUniformBuffer.h>

namespace MeteorEngine
{

	VulkanUniformBuffer::VulkanUniformBuffer(cp0* pointer , u32 size):

		VulkanBuffer(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, size, pointer)
	{
		SetData(pointer, size);
	}
	VulkanUniformBuffer::~VulkanUniformBuffer()
	{

	}
	void VulkanUniformBuffer::SetData(cp0* pointer, u32 size)
	{
		VulkanBuffer::Map();
		memcpy(m_Mapped, pointer, size);
		VulkanBuffer::UnMap();
	}
}