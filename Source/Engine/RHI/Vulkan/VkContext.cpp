#include <Engine/Render/Vulkan/VkContext.h>

namespace MeteorEngine
{

	VulkanContext* VulkanContext::m_ThisInstance = NULL;
	VulkanContext::VulkanContext():
		m_Instance(0),
		m_VulkanDevice(0),
		m_Surface(0)

	{
		m_ThisInstance = this;
	}
	VulkanContext::VulkanContext(Window* window):
		m_Instance(0),
		m_Surface(0)
	{
		m_ThisInstance = this;
		m_VulkanDevice = new VulkanDevice();
		Create(window);
	}

	VulkanContext::~VulkanContext()
	{
		if (m_Instance)
			vkDestroyInstance(m_Instance, 0);
	}
	void VulkanContext::Create(Window* window)
	{
		if (!CreateInstance(true)) 
		{
			LOG("Failed to Create a Instance!\n");
			return;
		}
		if (!m_VulkanDevice->Create())
		{
			LOG("Failed to Create a Device!\n");
			return;
		}
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
		surfaceCreateInfo.hwnd = static_cast<HWND>(window->GetWindowPtr());
		if (vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, 0, &m_Surface) != VK_SUCCESS) {
			LOG("Failed to Create a Surface!\n");
			return ;
		}
	}
	bool VulkanContext::CreateInstance(bool isDebug)
	{
		u32 objectCount = 0;
		if (vkEnumerateInstanceLayerProperties(&objectCount, 0) != VK_SUCCESS)
			return false;

		std::vector<VkLayerProperties> layers(objectCount);

		if (vkEnumerateInstanceLayerProperties(&objectCount, layers.data()) != VK_SUCCESS)
			return false;

		// Activate the layers we are interested in
		std::vector<const char*> validationLayers;

		for (VkLayerProperties& layer : layers)
		{
			if (!std::strcmp(layer.layerName, "VK_LAYER_LUNARG_standard_validation"))
				validationLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			else if (!std::strcmp(layer.layerName, "VK_LAYER_LUNARG_monitor"))
				validationLayers.push_back("VK_LAYER_LUNARG_monitor");
		}


		std::vector<const char*> requiredExtentions;
		{
			requiredExtentions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
			requiredExtentions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

			if (isDebug)
				requiredExtentions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		// Register our application information
		VkApplicationInfo applicationInfo	= VkApplicationInfo();
		applicationInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName	= "Runtime";
		applicationInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName			= "Meteor";
		applicationInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.apiVersion			= VK_API_VERSION_1_2;

		VkInstanceCreateInfo instanceCreateInfo		= VkInstanceCreateInfo();
		instanceCreateInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo			= &applicationInfo;
		instanceCreateInfo.enabledLayerCount		= static_cast<u32>(validationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames		= validationLayers.data();
		instanceCreateInfo.enabledExtensionCount	= static_cast<u32>(requiredExtentions.size());
		instanceCreateInfo.ppEnabledExtensionNames	= requiredExtentions.data();

		VkResult result = vkCreateInstance(&instanceCreateInfo, 0, &m_Instance);

		// If an extension is missing, try disabling debug report
		if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
		{
			//requiredExtentions.pop_back();

			instanceCreateInfo.enabledExtensionCount = static_cast<u32>(requiredExtentions.size());
			instanceCreateInfo.ppEnabledExtensionNames = requiredExtentions.data();

			result = vkCreateInstance(&instanceCreateInfo, 0, &m_Instance);
		}

		if (result != VK_SUCCESS)
			return false;



		return true;
	}
}
