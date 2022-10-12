#include <Engine/Render/Vulkan/VkCommandPool.h>
namespace MeteorEngine
{

	VulkanCommandPool::VulkanCommandPool() :
		m_Device(0),
		m_CommandPool(0)
	{
	}

	VulkanCommandPool::VulkanCommandPool(VkDevice device, u32 queueIndex) :
		m_Device(device),
		m_CommandPool(0)
	{
		Create(m_Device, queueIndex);
	}
	bool VulkanCommandPool::Create(VkDevice device, u32 queueIndex)
	{
		m_Device = device;
		// We want to be able to reset command buffers after submitting them
		VkCommandPoolCreateInfo commandPoolCreateInfo	= VkCommandPoolCreateInfo();
		commandPoolCreateInfo.sType						= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex			= queueIndex;
		commandPoolCreateInfo.flags						= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		// Create our command pool
		if (vkCreateCommandPool(m_Device, &commandPoolCreateInfo, 0, &m_CommandPool) != VK_SUCCESS)
			return false;


		return true;

	}
	VulkanCommandPool::~VulkanCommandPool()
	{
		if (m_CommandPool)
			vkDestroyCommandPool(m_Device, m_CommandPool, 0);
	}
}