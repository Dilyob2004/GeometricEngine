#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <assert.h>
namespace MeteorEngine
{
	VulkanDevice* VulkanDevice::thisInstance = NULL;
	VulkanDevice::VulkanDevice():
		m_DepthFormat(),
		m_QueueFamilyIndex(-1),
		m_PhysicalDevice(0),
		m_Device(0),
		m_Queue(0),
		m_Surface(0)
	{
		thisInstance = this;
	}	
	VulkanDevice::~VulkanDevice()
	{
		if (m_Device)
			vkDeviceWaitIdle(m_Device);
		if (m_Device)
			vkDestroyDevice(m_Device, 0);

		if (m_Surface)
			vkDestroySurfaceKHR(VulkanContext::GetInstance()->GetVkInstance(), m_Surface, 0);
	}

	bool VulkanDevice::CreateSurface(void* window)
	{
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo	= VkWin32SurfaceCreateInfoKHR();
		surfaceCreateInfo.sType							= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance						= (HINSTANCE) GetModuleHandle(NULL);
		surfaceCreateInfo.hwnd							= (HWND) window;
		if (vkCreateWin32SurfaceKHR(VulkanContext::GetInstance()->GetVkInstance(), &surfaceCreateInfo, nullptr, &m_Surface) != VK_SUCCESS)
			return false;


		return true;
	}
	bool VulkanDevice::CreateDevice()
	{
		VkInstance instance = VulkanContext::GetInstance()->GetVkInstance();
		// Retrieve list of GPUs
		u32 objectCount = 0;

		if (vkEnumeratePhysicalDevices(instance, &objectCount, 0) != VK_SUCCESS)
			return false;

		std::vector<VkPhysicalDevice> devices(objectCount);

		if (vkEnumeratePhysicalDevices(instance, &objectCount, devices.data()) != VK_SUCCESS)
			return false;

		// Look for a GPU that supports swapchains
		for (VkPhysicalDevice dev : devices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(dev, &deviceProperties);


			if (vkEnumerateDeviceExtensionProperties(dev, 0, &objectCount, 0) != VK_SUCCESS)
				return false;

			std::vector<VkExtensionProperties> extensions(objectCount);

			if (vkEnumerateDeviceExtensionProperties(dev, 0, &objectCount, extensions.data()) != VK_SUCCESS)			
				return false;
			

			bool supportsSwapchain = false;

			for (VkExtensionProperties& extension : extensions)
			{
				if (!std::strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME))
				{
					supportsSwapchain = true;
					break;
				}
			}

			if (!supportsSwapchain)
				continue;

			// Prefer discrete over integrated GPUs if multiple are available
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				m_PhysicalDevice = dev;
				break;
			}
			else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				m_PhysicalDevice = dev;
		}

		if (!m_PhysicalDevice)
			return false;

		// Check what depth formats are available and select one
		VkFormatProperties formatProperties = VkFormatProperties();

		vkGetPhysicalDeviceFormatProperties(m_PhysicalDevice, VK_FORMAT_D24_UNORM_S8_UINT, &formatProperties);

		if (formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			m_DepthFormat = VK_FORMAT_D24_UNORM_S8_UINT;
		else
		{
			vkGetPhysicalDeviceFormatProperties(m_PhysicalDevice, VK_FORMAT_D32_SFLOAT_S8_UINT, &formatProperties);

			if (formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				m_DepthFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;
			else
			{
				vkGetPhysicalDeviceFormatProperties(m_PhysicalDevice, VK_FORMAT_D32_SFLOAT, &formatProperties);

				if (formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
					m_DepthFormat = VK_FORMAT_D32_SFLOAT;
				else
					return false;
			}
		}



		// Select a queue family that supports graphics operations and surface presentation
		objectCount = 0;


		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &objectCount, 0);

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(objectCount);

		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &objectCount, queueFamilyProperties.data());

		for (std::size_t i = 0; i < queueFamilyProperties.size(); ++i)
		{
			VkBool32 surfaceSupported = VK_FALSE;

			vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, static_cast<u32>(i), m_Surface, &surfaceSupported);

			if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (surfaceSupported == VK_TRUE))
			{
				m_QueueFamilyIndex = static_cast<s32>(i);
				break;
			}
		}

		if (m_QueueFamilyIndex < 0)
			return false;

		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo deviceQueueCreateInfo = VkDeviceQueueCreateInfo();
		deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueCreateInfo.queueCount = 1;
		deviceQueueCreateInfo.queueFamilyIndex = static_cast<u32>(m_QueueFamilyIndex);
		deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

		// Enable the swapchain extension
		const char* extentions[1] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		// Enable anisotropic filtering
		VkPhysicalDeviceFeatures physicalDeviceFeatures = VkPhysicalDeviceFeatures();
		physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

		VkDeviceCreateInfo deviceCreateInfo			= VkDeviceCreateInfo();
		deviceCreateInfo.sType						= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.enabledExtensionCount		= 1;
		deviceCreateInfo.ppEnabledExtensionNames	= extentions;
		deviceCreateInfo.queueCreateInfoCount		= 1;
		deviceCreateInfo.pQueueCreateInfos			= &deviceQueueCreateInfo;
		deviceCreateInfo.pEnabledFeatures			= &physicalDeviceFeatures;

		// Create our logical device
		if (vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, 0, &m_Device) != VK_SUCCESS)
			return false;

		// Retrieve a handle to the logical device command queue
		vkGetDeviceQueue(m_Device, static_cast<u32>(m_QueueFamilyIndex), 0, &m_Queue);
	}
}