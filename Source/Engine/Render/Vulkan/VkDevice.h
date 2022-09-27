#ifndef VKDEVICE_H
#define VKDEVICE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Core/Singleton.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanDevice 
	{
	public:
		static VulkanDevice* GetInstance() { return thisInstance; }
		VulkanDevice();
		~VulkanDevice();
		VkPhysicalDevice	GetPhysicalDevice() const { return m_PhysicalDevice; }
		VkDevice			GetLogicalDevice() const { return m_Device; }
		VkSurfaceKHR		GetSurface() const { return m_Surface; }
		VkFormat			GetSupportDepthFormat() const { return m_DepthFormat; }
		VkQueue				GetQueue() const { return m_Queue; }
		s32					GetQueueFamilyIndex() const { return m_QueueFamilyIndex; }
		bool CreateSurface(void*);
		bool CreateDevice();
	private:
		static VulkanDevice* thisInstance;
		s32								m_QueueFamilyIndex;
		VkPhysicalDevice				m_PhysicalDevice;
		VkDevice						m_Device;
		VkFormat						m_DepthFormat;
		VkQueue							m_Queue;
		VkSurfaceKHR					m_Surface;


	};
}
#endif // !VKDEVICE_H
