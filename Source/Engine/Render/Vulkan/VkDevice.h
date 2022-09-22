#ifndef VKDEVICE_H
#define VKDEVICE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <vector>

namespace MeteorEngine
{
	class METEOR_API VulkanDevice
	{
	public:
		struct
		{
			u32 graphics;
			u32 compute;
			u32 transfer;
		} queueFamilyIndices;
		operator VkDevice() const
		{
			return m_Device;
		};
		explicit VulkanDevice(VkPhysicalDevice);
		~VulkanDevice();
		VkResult CreateDevice(VkPhysicalDeviceFeatures, std::vector<const char*>, void*, bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
	private:	
		
		VkCommandPool CreateCommandPool(u32, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		u32 GetMemoryType(u32, VkMemoryPropertyFlags, VkBool32* memTypeFound = nullptr) const;
		u32 GetQueueFamilyIndex(VkQueueFlags) const;
		bool ExtensionSupported(std::string extension)
		{
			return (std::find(m_SupportedExtensions.begin(), m_SupportedExtensions.end(), extension) != m_SupportedExtensions.end());
		}
		VkPhysicalDevice					m_PhysicalDevice;
		VkDevice							m_Device;

		/** @brief Properties of the physical device including limits that the application can check against */
		VkPhysicalDeviceProperties			m_Properties;

		/** @brief Features of the physical device that an application can use to check if a feature is supported */
		VkPhysicalDeviceFeatures			m_Features;

		/** @brief Features that have been enabled for use on the physical device */
		VkPhysicalDeviceFeatures			m_EnabledFeatures;

		/** @brief Memory types and heaps of the physical device */
		VkPhysicalDeviceMemoryProperties	m_MemoryProperties;

		/** @brief Queue family properties of the physical device */
		std::vector<VkQueueFamilyProperties> m_QueueFamilyProperties;

		/** @brief List of extensions supported by the device */
		std::vector<std::string> m_SupportedExtensions;

		/** @brief Default command pool for the graphics queue family index */
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;

		/** @brief Set to true when the debug marker extension is detected */
		bool m_EnableDebugMarkers = false;
	};
}
#endif // !VKDEVICE_H
