#ifndef VKCOMMANDPOOL_H
#define VKCOMMANDPOOL_H

#include <Engine/Render/Vulkan/Vk.h>
namespace MeteorEngine
{
	class METEOR_API VulkanCommandPool
	{
	public:
		VulkanCommandPool();
		VulkanCommandPool(VkDevice, u32);
		~VulkanCommandPool();
		bool Create(VkDevice, u32);
		VkCommandPool GetCommandPool() const { return m_CommandPool; }
	private:
		VkDevice m_Device;
		VkCommandPool m_CommandPool;
	};
}
#endif // !VKCOMMANDPOOL_H
