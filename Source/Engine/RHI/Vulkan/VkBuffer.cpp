#include <Engine/Render/Vulkan/VkBuffer.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkUtilities.h>


namespace MeteorEngine
{

	VulkanBuffer::VulkanBuffer(VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperyFlags, u32 size, const void* data) :
		m_Size(size)
	{
		Create(usage, memoryProperyFlags, size, data);
	}
	VulkanBuffer::VulkanBuffer() :
		m_Size(0)
	{

	}
	VulkanBuffer::~VulkanBuffer()
	{
		if (m_Buffer)
			vkDestroyBuffer(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Buffer, NULL);

		if (m_Memory)
			vkFreeMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Memory, NULL);
	}

	void VulkanBuffer::Create(VkBufferUsageFlags usage, VkMemoryPropertyFlags memoryProperyFlags, u32 size, const void* data)
	{

		m_UsageFlags = usage;
		m_MemoryProperyFlags = memoryProperyFlags;
		m_Size = size;

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		bool isMappable = (memoryProperyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0;

		if (vkCreateBuffer(VulkanDevice::GetInstance()->GetLogicalDevice(), &bufferInfo, nullptr, &m_Buffer) != VK_SUCCESS)
		{
			LOG("[Vulkan] Failed to Create Buffer!\n");
			return;
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Buffer, 
										&memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(VulkanDevice::GetInstance()->GetPhysicalDevice(), 
													memRequirements.memoryTypeBits, 
													VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | 
													VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if(vkAllocateMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), &allocInfo, nullptr, &m_Memory) != VK_SUCCESS)
		{
			LOG("[Vulkan] Failed to Allocate Memory Buffer!\n");
			return;
		}

		vkBindBufferMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Buffer, m_Memory, 0);

		if (data != nullptr)
			SetData(size, data);
	}
	void VulkanBuffer::Resize(u32 size, const void* data)
	{
		if (m_Buffer)
			vkDestroyBuffer(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Buffer, NULL);
		if (m_Memory)
			vkFreeMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Memory, NULL);
		Create(m_UsageFlags, m_MemoryProperyFlags, size, data);
	}
	void VulkanBuffer::SetData(u32 size, const void* data)
	{
		Map(size, 0);
		memcpy(m_Mapped, data, size);
		UnMap();
	}

	void VulkanBuffer::Map(VkDeviceSize size, VkDeviceSize offset)
	{
		if (vkMapMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Memory, offset, size, 0, &m_Mapped) != VK_SUCCESS)
			LOG("[Vulkan] Failed to map buffer");
	}
	void VulkanBuffer::UnMap()
	{
		if (m_Mapped)
		{
			vkUnmapMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Memory);
			m_Mapped = NULL;
		}
	}
	void VulkanBuffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{

		VkMappedMemoryRange mappedRange = {};
		mappedRange.memory = m_Memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		vkFlushMappedMemoryRanges(VulkanDevice::GetInstance()->GetLogicalDevice(), 1, &mappedRange);
	}
	void VulkanBuffer::Invalidate(VkDeviceSize size, VkDeviceSize offset)
	{
		VkMappedMemoryRange mappedRange = {};
		mappedRange.memory = m_Memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		vkInvalidateMappedMemoryRanges(VulkanDevice::GetInstance()->GetLogicalDevice(), 1, &mappedRange);
	}
	void VulkanBuffer::Destroy(bool deletionQueue)
	{

	}
}