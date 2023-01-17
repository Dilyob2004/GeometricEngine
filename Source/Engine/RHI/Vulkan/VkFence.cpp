#include <Engine/Render/Vulkan/VkFence.h>
#include <Engine/Render/Vulkan/VkDevice.h>

namespace MeteorEngine
{
	VulkanFence::VulkanFence() :
		m_Fence(0),
		m_Device(0)
	{
	}

	bool VulkanFence::Create(VkDevice device)
	{
		m_Device = device;
		// Create the fences in the signaled state
		VkFenceCreateInfo fenceCreateInfo = VkFenceCreateInfo();
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		if (vkCreateFence(m_Device, &fenceCreateInfo, 0, &m_Fence) != VK_SUCCESS) 
			return false;

		return true;
	}
	VulkanFence::~VulkanFence()
	{
		if(m_Fence)
			vkDestroyFence(m_Device, m_Fence, 0);
	}
	void VulkanFence::Wait()
	{
		vkWaitForFences(m_Device, 1, &m_Fence, VK_TRUE, UINT64_MAX);
	}
	void VulkanFence::Reset()
	{
		vkResetFences(m_Device, 1, &m_Fence);
	}
}