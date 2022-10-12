#ifndef VKDEVICE_H
#define VKDEVICE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkCommandPool.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanDevice 
	{
	public:
		static VulkanDevice* GetInstance() { return m_ThisInstance; }
		VulkanDevice();
		~VulkanDevice();
		VkPhysicalDevice	GetPhysicalDevice() const { return m_PhysicalDevice; }
		VkDevice			GetLogicalDevice() const { return m_Device; }
		VkQueue				GetQueue() const { return m_Queue; }
		u32					GetQueueFamilyIndex() const { return m_QueueFamilyIndex; }

		VkPipelineCache GetPipelineCache() const  { return m_PipelineCache; }
		VulkanCommandPool* GetCommandPool() const { return m_CommandPool; }
		bool Create(); 
		void WaitIdle()
		{
			vkDeviceWaitIdle(m_Device);
		}
	private:
		void CreateTracyContext();
		void CreatePipelineCache();
		static VulkanDevice*			m_ThisInstance;


		VkPipelineCache					m_PipelineCache;
		VulkanCommandPool*				m_CommandPool;
		u32								m_QueueFamilyIndex;
		VkPhysicalDevice				m_PhysicalDevice;
		VkDevice						m_Device;
		VkQueue							m_Queue;

	};
}
#endif // !VKDEVICE_H
