#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <assert.h>
namespace MeteorEngine
{
	VulkanDevice* VulkanDevice::m_ThisInstance = NULL;
	VulkanDevice::VulkanDevice():
		m_PipelineCache(0),
		m_CommandPool(0),
		m_QueueFamilyIndex(-1),
		m_PhysicalDevice(0),
		m_Device(0),
		m_Queue(0)
	{
		m_ThisInstance = this;
	}	
	VulkanDevice::~VulkanDevice()
	{
		if (m_Device) {
			vkDeviceWaitIdle(m_Device);
			vkDestroyDevice(m_Device, 0);
		}
	}

	void VulkanDevice::CreateTracyContext()
	{

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool->GetCommandPool();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer tracyBuffer;
		vkAllocateCommandBuffers(m_Device, &allocInfo, &tracyBuffer);
		/**
		
		
		*/
		vkQueueWaitIdle(m_Queue);
		vkFreeCommandBuffers(m_Device, m_CommandPool->GetCommandPool(), 1, &tracyBuffer);
	}
	void VulkanDevice::CreatePipelineCache()
	{
		VkPipelineCacheCreateInfo pipelineCacheCI = {};
		pipelineCacheCI.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		pipelineCacheCI.pNext = NULL;
		vkCreatePipelineCache(m_Device, &pipelineCacheCI, VK_NULL_HANDLE, &m_PipelineCache);
	}
	bool VulkanDevice::Create()
	{
		VkInstance m_Instance = VulkanContext::GetInstance()->GetVulkanInstance();

		u32 objectCount = 0;

		if (vkEnumeratePhysicalDevices(m_Instance, &objectCount, 0) != VK_SUCCESS)
			return false;

		std::vector<VkPhysicalDevice> devices(objectCount);
		if (vkEnumeratePhysicalDevices(m_Instance, &objectCount, devices.data()) != VK_SUCCESS)
			return false;
		
		for (VkPhysicalDevice i : devices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(i, &deviceProperties);

			if (vkEnumerateDeviceExtensionProperties(i, 0, &objectCount, 0) != VK_SUCCESS)
				return false;

			std::vector<VkExtensionProperties> extensions(objectCount);

			if (vkEnumerateDeviceExtensionProperties(i, 0, &objectCount, extensions.data()) != VK_SUCCESS)			
				return false;
			

			bool supportsSwapchain = false;

			for (VkExtensionProperties& extension : extensions)
				if (!std::strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME))
				{
					supportsSwapchain = true;
					break;
				}

			if (!supportsSwapchain)
				continue;


			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				m_PhysicalDevice = i;
				break;
			}
			else if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				m_PhysicalDevice = i;
		}

		if (!m_PhysicalDevice)
			return false;

		objectCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &objectCount, 0);

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(objectCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &objectCount, queueFamilyProperties.data());

		for (u32 i = 0; i < queueFamilyProperties.size(); ++i)
		{
			if ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
			{
				m_QueueFamilyIndex = i;
				break;
			}
		}

		if (m_QueueFamilyIndex < 0)
			return false;

		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo deviceQueueCreateInfo	= VkDeviceQueueCreateInfo();
		deviceQueueCreateInfo.sType						= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueCreateInfo.queueCount				= 1;
		deviceQueueCreateInfo.queueFamilyIndex			= m_QueueFamilyIndex;
		deviceQueueCreateInfo.pQueuePriorities			= &queuePriority;

		const char* extentions[1] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		VkPhysicalDeviceFeatures physicalDeviceFeatures = VkPhysicalDeviceFeatures();
		physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

		VkDeviceCreateInfo deviceCreateInfo			= VkDeviceCreateInfo();
		deviceCreateInfo.sType						= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.enabledExtensionCount		= 1;
		deviceCreateInfo.ppEnabledExtensionNames	= extentions;
		deviceCreateInfo.queueCreateInfoCount		= 1;
		deviceCreateInfo.pQueueCreateInfos			= &deviceQueueCreateInfo;
		deviceCreateInfo.pEnabledFeatures			= &physicalDeviceFeatures;

		if (vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, 0, &m_Device) != VK_SUCCESS)
			return false;

		vkGetDeviceQueue(m_Device, m_QueueFamilyIndex, 0, &m_Queue);


		m_CommandPool = new VulkanCommandPool();
		m_CommandPool->Create(m_Device, m_QueueFamilyIndex);

		CreatePipelineCache();
		//CreateTracyContext();
	}
}