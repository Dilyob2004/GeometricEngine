#include <Engine/Render/Vulkan/VkVertexBuffer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
namespace MeteorEngine
{

	VulkanVertexBuffer::VulkanVertexBuffer(cp0 vertexPointer, u32 size): VulkanBuffer(),
		m_Size(size),
		m_MappedBuffer(false)
	{
		VulkanBuffer::SetUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		VulkanBuffer::SetMemoryProperyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
		
		SetData(vertexPointer, m_Size);
	}
	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		if(m_MappedBuffer)
		{
			VulkanBuffer::Flush(m_Size);
			VulkanBuffer::UnMap();

			m_MappedBuffer = false;
		}
	}
	void VulkanVertexBuffer::Bind(CommandBuffer* commandBuffer)
	{
		VkDeviceSize offsets[1] = { 0 };
		if (commandBuffer)
			vkCmdBindVertexBuffers(dynamic_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), 0, 1, &m_Buffer, offsets);
	}
	void VulkanVertexBuffer::SetData(cp0 vertexPointer, u32 size)
	{
		VulkanBuffer::SetData(size, vertexPointer);
	}
	void VulkanVertexBuffer::Resize(u32 size)
	{
		m_Size = size;
		VulkanBuffer::Resize(m_Size, NULL);
	}
}