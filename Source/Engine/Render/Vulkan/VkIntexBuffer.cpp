#include <Engine/Render/Vulkan/VkIntexBuffer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>

namespace MeteorEngine
{
	VulkanIndexBuffer::VulkanIndexBuffer(u32* pointer, u32 count):
	    VulkanBuffer(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, count * sizeof(u32), pointer),
		m_Size(count * sizeof(u32)),
		m_Count(count)
	{

	}
	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		if (m_MappedBuffer)
		{
			VulkanBuffer::Flush(m_Size);
			VulkanBuffer::UnMap();

			m_MappedBuffer = false;
		}
	}

	void VulkanIndexBuffer::Bind(CommandBuffer* commandBuffer) const
	{
		vkCmdBindIndexBuffer(dynamic_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), m_Buffer, 0, VK_INDEX_TYPE_UINT32);
	}
	void VulkanIndexBuffer::UnBind() const
	{

	}
}