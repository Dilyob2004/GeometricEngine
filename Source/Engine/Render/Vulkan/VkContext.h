#ifndef VKCONTEXT_H
#define VKCONTEXT_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkSwapchain.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanContext
	{
	public:
		VulkanContext();
		~VulkanContext();

		bool Init();


	private:
		void CreateInstance(bool);

		VkInstance		m_Instance;
		VulkanDevice	*m_VulkanDevice;
		VulkanSwapChain *m_VulkanSwapChain;
		VkPhysicalDevice m_PhysicalDevice;

		VkQueue m_Queue;
		VkPhysicalDeviceFeatures m_EnabledFeatures{};

		/** @brief Optional pNext structure for passing extension structures to device creation */
		void* m_DeviceCreatepNextChain = nullptr;
		std::vector<std::string> m_SupportedInstanceExtensions;

		std::vector<const char*> m_EnabledDeviceExtensions;
		std::vector<const char*> m_EnabledInstanceExtensions;
	};
}
#endif // !VKCONTEXT_Hâ
