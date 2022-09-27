#include <Engine/Render/Vulkan/VkContext.h>
#include <Engine/Core/Application.h>

namespace MeteorEngine
{

	VulkanContext* VulkanContext::thisInstance = NULL;
	VulkanContext::VulkanContext() :
		m_CommandPool(0),
		m_Fences(0),
		m_MaxFramesInFlight(2),
		m_Instance(0),
		m_ImageAvailableSemaphores(),
		m_RenderFinishedSemaphores(),
		m_CommandBuffers()
	{
		thisInstance = this;
		if (!CreateInstance(true))
			LOG("Failed to Create a Instance!\n");
		m_VulkanDevice		= new VulkanDevice();
		m_VulkanSwapChain	= new VulkanSwapChain();
		m_VulkanFrameBuffer = new VulkanFrameBuffer();
	}

	VulkanContext::~VulkanContext()
	{
		for (VkFence fence : m_Fences)
			vkDestroyFence(m_VulkanDevice->GetLogicalDevice(), fence, 0);

		for (VkSemaphore renderFinishedSemaphore : m_RenderFinishedSemaphores)
			vkDestroySemaphore(m_VulkanDevice->GetLogicalDevice(), renderFinishedSemaphore, 0);

		for (VkSemaphore imageAvailableSemaphore : m_ImageAvailableSemaphores)
			vkDestroySemaphore(m_VulkanDevice->GetLogicalDevice(), imageAvailableSemaphore, 0);
		
		if (m_CommandPool)
			vkDestroyCommandPool(m_VulkanDevice->GetLogicalDevice(), m_CommandPool, 0);

		if (m_Instance)
			vkDestroyInstance(m_Instance, 0);
	}
	void VulkanContext::Create(Window * window)
	{
		if (!m_VulkanDevice->CreateSurface(window->GetWindowPtr()))
		{
			LOG("Failed to Create a Surface!\n");
			return;
		}
		if (!m_VulkanDevice->CreateDevice())
		{
			LOG("Failed to Create a Device!\n");
			return;
		}

		

		if (!m_VulkanSwapChain->CreateSwapChain(window->GetSize().x, window->GetSize().y))
		{
			LOG("Failed to Create a Swap Chain!\n");
			return;
		}

		if (!CreateCommandPool())
		{
			LOG("Failed to Create a Command Pool!\n");
			return;
		}


		if (!m_VulkanFrameBuffer->CreateFrameBuffer(window->GetSize().x, window->GetSize().y))
		{
			LOG("Failed to Create a Frame Buffer!\n");
			return;

		}

		if (!AllocateCommandBuffer())
		{
			LOG("Failed to Allocate a Command Buffer!\n");
			return;
		}

		if (!CreateSemaphores())
		{
			LOG("Failed to Create a Semaphores!\n");
			return;
		}

		if (!CreateFences())
		{
			LOG("Failed to Create a Fences!\n");
			return;
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
			// VK_LAYER_LUNARG_standard_validation, meta-layer for the following layers:
			// -- VK_LAYER_GOOGLE_threading
			// -- VK_LAYER_LUNARG_parameter_validation
			// -- VK_LAYER_LUNARG_device_limits
			// -- VK_LAYER_LUNARG_object_tracker
			// -- VK_LAYER_LUNARG_image
			// -- VK_LAYER_LUNARG_core_validation
			// -- VK_LAYER_LUNARG_swapchain
			// -- VK_LAYER_GOOGLE_unique_objects
			// These layers perform error checking and warn about bad or sub-optimal Vulkan API usage
			// VK_LAYER_LUNARG_monitor appends an FPS counter to the window title
			if (!std::strcmp(layer.layerName, "VK_LAYER_LUNARG_standard_validation"))
				validationLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			else if (!std::strcmp(layer.layerName, "VK_LAYER_LUNARG_monitor"))
				validationLayers.push_back("VK_LAYER_LUNARG_monitor");
		}


		std::vector<const char*> requiredExtentions;

		requiredExtentions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		requiredExtentions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

		if (isDebug)
			requiredExtentions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

		// Register our application information
		VkApplicationInfo applicationInfo = VkApplicationInfo();
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = "Runtime";
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName = "Meteor";
		applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.apiVersion = VK_API_VERSION_1_2;

		VkInstanceCreateInfo instanceCreateInfo = VkInstanceCreateInfo();
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
		instanceCreateInfo.enabledExtensionCount = static_cast<u32>(requiredExtentions.size());
		instanceCreateInfo.ppEnabledExtensionNames = requiredExtentions.data();

		VkResult result = vkCreateInstance(&instanceCreateInfo, 0, &m_Instance);

		// If an extension is missing, try disabling debug report
		if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
		{
			requiredExtentions.pop_back();

			instanceCreateInfo.enabledExtensionCount = static_cast<u32>(requiredExtentions.size());
			instanceCreateInfo.ppEnabledExtensionNames = requiredExtentions.data();

			result = vkCreateInstance(&instanceCreateInfo, 0, &m_Instance);
		}

		if (result != VK_SUCCESS)
			return false;



		return true;
	}
	bool VulkanContext::CreateCommandPool()
	{

		// We want to be able to reset command buffers after submitting them
		VkCommandPoolCreateInfo commandPoolCreateInfo = VkCommandPoolCreateInfo();
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = static_cast<u32>(m_VulkanDevice->GetQueueFamilyIndex());
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		// Create our command pool
		if (vkCreateCommandPool(m_VulkanDevice->GetLogicalDevice(), &commandPoolCreateInfo, 0, &m_CommandPool) != VK_SUCCESS)
			return false;


		return true;
	}
	bool VulkanContext::AllocateCommandBuffer()
	{
		// We need a command buffer for every frame in flight
		m_CommandBuffers.resize(m_VulkanFrameBuffer->GetFrameBuffer().size());

		// These are primary command buffers
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = VkCommandBufferAllocateInfo();
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = m_CommandPool;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandBufferCount = static_cast<u32>(m_CommandBuffers.size());

		// Allocate the command buffers from our command pool
		if (vkAllocateCommandBuffers(m_VulkanDevice->GetLogicalDevice(), &commandBufferAllocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		{
			m_CommandBuffers.clear();
			return false;
		}
		return true;
	}
	bool VulkanContext::CreateSemaphores()
	{

		VkSemaphoreCreateInfo semaphoreCreateInfo = VkSemaphoreCreateInfo();
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		// Create a semaphore to track when an swapchain image is available for each frame in flight
		for (u32 i = 0; i < m_MaxFramesInFlight; i++)
		{
			m_ImageAvailableSemaphores.push_back(0);

			if (vkCreateSemaphore(m_VulkanDevice->GetLogicalDevice(), &semaphoreCreateInfo, 0, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS)
			{
				m_ImageAvailableSemaphores.pop_back();
				return false;
			}
		}

		// Create a semaphore to track when rendering is complete for each frame in flight
		for (u32 i = 0; i < m_MaxFramesInFlight; i++)
		{
			m_RenderFinishedSemaphores.push_back(0);

			if (vkCreateSemaphore(m_VulkanDevice->GetLogicalDevice(), &semaphoreCreateInfo, 0, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS)
			{
				m_RenderFinishedSemaphores.pop_back();
				return false;
			}
		}

		return true;
	}
	bool VulkanContext::CreateFences()
	{

		// Create the fences in the signaled state
		VkFenceCreateInfo fenceCreateInfo = VkFenceCreateInfo();
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		// Create a fence to track when queue submission is complete for each frame in flight
		for (u32 i = 0; i < m_MaxFramesInFlight; i++)
		{
			m_Fences.push_back(0);
			if (vkCreateFence(m_VulkanDevice->GetLogicalDevice(), &fenceCreateInfo, 0, &m_Fences[i]) != VK_SUCCESS)
			{
				m_Fences.pop_back();
				return false;
			}
		}
		return true;
	}

	void VulkanContext::Present()
	{

		std::uint32_t imageIndex = 0;

		// If the objects we need to submit this frame are still pending, wait here

		vkWaitForFences(m_VulkanDevice->GetLogicalDevice(), 1, &m_Fences[currentFrame], VK_TRUE, UINT64_MAX);

		{
			// Get the next image in the swapchain
			VkResult result = vkAcquireNextImageKHR(m_VulkanDevice->GetLogicalDevice(),
				m_VulkanSwapChain->GetSwapChain(),
				UINT64_MAX,
				m_ImageAvailableSemaphores[currentFrame],
				VK_NULL_HANDLE,
				&imageIndex);
			// Check if we need to re-create the swapchain (e.g. if the window was resized)
			if (result == VK_ERROR_OUT_OF_DATE_KHR)
			{
				//recreateSwapchain();
				swapchainOutOfDate = false;
				return;
			}

			if ((result != VK_SUCCESS) && (result != VK_TIMEOUT) && (result != VK_NOT_READY) &&
				(result != VK_SUBOPTIMAL_KHR))
				return;
		}
		if (!m_CommandBuffers[imageIndex])
		{
			LOG("Eoor");
		}
		// Wait for the swapchain image to be available in the color attachment stage before submitting the queue
		VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		// Signal the render finished semaphore once the queue has been processed
		VkSubmitInfo submitInfo = VkSubmitInfo();
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &m_ImageAvailableSemaphores[currentFrame];
		submitInfo.pWaitDstStageMask = &waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_CommandBuffers[imageIndex];
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &m_RenderFinishedSemaphores[currentFrame];

		vkResetFences(m_VulkanDevice->GetLogicalDevice(), 1, &m_Fences[currentFrame]);

		if (vkQueueSubmit(m_VulkanDevice->GetQueue(), 1, &submitInfo, m_Fences[currentFrame]) != VK_SUCCESS)
			return;

		// Wait for rendering to complete before presenting
		VkPresentInfoKHR presentInfo = VkPresentInfoKHR();
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &m_RenderFinishedSemaphores[currentFrame];
		presentInfo.swapchainCount = 1;
		VkSwapchainKHR pSwapchains = m_VulkanSwapChain->GetSwapChain();

		presentInfo.pSwapchains = &pSwapchains;
		presentInfo.pImageIndices = &imageIndex;

		{
			// Queue presentation
			VkResult result = vkQueuePresentKHR(m_VulkanDevice->GetQueue(), &presentInfo);

			// Check if we need to re-create the swapchain (e.g. if the window was resized)
			if ((result == VK_ERROR_OUT_OF_DATE_KHR) || (result == VK_SUBOPTIMAL_KHR) || swapchainOutOfDate)
			{
				//recreateSwapchain();
				swapchainOutOfDate = false;
			}
			else if (result != VK_SUCCESS)
				return;
		}

		// Make sure to use the next frame's objects next frame
		currentFrame = (currentFrame + 1) % m_MaxFramesInFlight;
	}
}