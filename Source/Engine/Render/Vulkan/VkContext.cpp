#include <Engine/Render/Vulkan/VkContext.h>
#include <Engine/Core/Application.h>

namespace MeteorEngine
{
	VulkanContext::VulkanContext()
	{
		Init();
	}

	VulkanContext::~VulkanContext()
	{

	}
	bool VulkanContext::Init()
	{
		CreateInstance(true);
		uint32_t gpuCount = 0;
		// Get number of available physical devices
		vkEnumeratePhysicalDevices(m_Instance, &gpuCount, nullptr);
		if (gpuCount == 0) {
			LOG("No device with Vulkan support found");
			return false;
		}
		// Enumerate devices
		std::vector<VkPhysicalDevice> physicalDevices(gpuCount);
		VkResult err = vkEnumeratePhysicalDevices(m_Instance, &gpuCount, physicalDevices.data());
		if (err) {
			LOG("Could not enumerate physical devices : \n");
			return false;
		}

		// GPU selection

		// Select physical device to be used for the Vulkan example
		// Defaults to the first device unless specified by command line
		uint32_t selectedDevice = 0;
		m_PhysicalDevice = physicalDevices[selectedDevice];



		m_VulkanDevice = new VulkanDevice(m_PhysicalDevice);
		m_VulkanDevice->CreateDevice(m_EnabledFeatures, m_EnabledDeviceExtensions, NULL);


		VkDevice device = *m_VulkanDevice;
		vkGetDeviceQueue(device, m_VulkanDevice->queueFamilyIndices.graphics, 0, &m_Queue);

		m_VulkanSwapChain = new VulkanSwapChain();
		m_VulkanSwapChain->Connect(m_Instance, m_PhysicalDevice, device);
		m_VulkanSwapChain->InitSurface(Application::GetInstance().GetWindow().GetWindowPtr());
		u32 w = 1280, h = 720;

		m_VulkanSwapChain->Create(&w, &h, true);
	}
	void VulkanContext::CreateInstance(bool enableValidation)
	{
		VkApplicationInfo applicationInfo = VkApplicationInfo();
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = "Runtime";
		applicationInfo.pEngineName = "Meteor";


		std::vector<const char*> instanceExtensions;
		instanceExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME );
		instanceExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);



		// Get extensions supported by the instance and store for later use
		uint32_t extCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
		if (extCount > 0)
		{
			std::vector<VkExtensionProperties> extensions(extCount);
			if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
				for (VkExtensionProperties extension : extensions)
					m_SupportedInstanceExtensions.push_back(extension.extensionName);
		}

		// Enabled requested instance extensions
		if (m_EnabledInstanceExtensions.size() > 0)
			for (const char* enabledExtension : m_EnabledInstanceExtensions)
			{
				// Output message if requested extension is not available
				if (std::find(m_SupportedInstanceExtensions.begin(), m_SupportedInstanceExtensions.end(), enabledExtension) == m_SupportedInstanceExtensions.end())
					std::cerr << "Enabled instance extension \"" << enabledExtension << "\" is not present at instance level\n";
				instanceExtensions.push_back(enabledExtension);
			}
		VkInstanceCreateInfo instanceCreateInfo = VkInstanceCreateInfo();
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pNext = NULL;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;

		if (instanceExtensions.size() > 0)
		{
			if (enableValidation)
			{
				instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);	// SRS - Dependency when VK_EXT_DEBUG_MARKER is enabled
				instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			}
			instanceCreateInfo.enabledExtensionCount = (u32)instanceExtensions.size();
			instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
		}

		// The VK_LAYER_KHRONOS_validation contains all current validation functionality.
		// Note that on Android this layer requires at least NDK r20
		const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
		if (enableValidation)
		{
			// Check if this layer is available at instance level
			uint32_t instanceLayerCount;
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);


			std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
			vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());


			bool validationLayerPresent = false;
			for (VkLayerProperties layer : instanceLayerProperties) 
				if (strcmp(layer.layerName, validationLayerName) == 0) {
					validationLayerPresent = true;
					break;
				}

			if (validationLayerPresent) {
				instanceCreateInfo.ppEnabledLayerNames = &validationLayerName;
				instanceCreateInfo.enabledLayerCount = 1;
			}
			else 
				std::cerr << "Validation layer VK_LAYER_KHRONOS_validation not present, validation is disabled";

			
			VK_CHECK(vkCreateInstance(&instanceCreateInfo, 0, &m_Instance), "vkCreateInstance");
		}



	}
}