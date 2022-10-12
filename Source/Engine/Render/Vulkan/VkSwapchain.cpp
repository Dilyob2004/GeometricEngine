
#include <Engine/Render/Vulkan/VkContext.h> 
#include <cassert>
namespace MeteorEngine
{
	VkPipelineStageFlags AccessFlagsToPipelineStage(VkAccessFlags accessFlags, const VkPipelineStageFlags stageFlags)
	{
		VkPipelineStageFlags stages = 0;

		while (accessFlags != 0)
		{
			VkAccessFlagBits AccessFlag = static_cast<VkAccessFlagBits>(accessFlags & (~(accessFlags - 1)));
			//ASSERT(AccessFlag != 0 && (AccessFlag & (AccessFlag - 1)) == 0, "Error");
			accessFlags &= ~AccessFlag;

			switch (AccessFlag)
			{
			case VK_ACCESS_INDIRECT_COMMAND_READ_BIT:
				stages |= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
				break;

			case VK_ACCESS_INDEX_READ_BIT:
				stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
				break;

			case VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT:
				stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
				break;

			case VK_ACCESS_UNIFORM_READ_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_INPUT_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				break;

			case VK_ACCESS_SHADER_READ_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_SHADER_WRITE_BIT:
				stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
				break;

			case VK_ACCESS_COLOR_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				break;

			case VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				break;

			case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT:
				stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
				break;

			case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
				break;

			case VK_ACCESS_TRANSFER_READ_BIT:
				stages |= VK_PIPELINE_STAGE_TRANSFER_BIT;
				break;

			case VK_ACCESS_TRANSFER_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_TRANSFER_BIT;
				break;

			case VK_ACCESS_HOST_READ_BIT:
				stages |= VK_PIPELINE_STAGE_HOST_BIT;
				break;

			case VK_ACCESS_HOST_WRITE_BIT:
				stages |= VK_PIPELINE_STAGE_HOST_BIT;
				break;

			case VK_ACCESS_MEMORY_READ_BIT:
				break;

			case VK_ACCESS_MEMORY_WRITE_BIT:
				break;

			default:
				LOG("Unknown access flag");
				break;
			}
		}
		return stages;
	}
	VkPipelineStageFlags LayoutToAccessMask(const VkImageLayout layout, const bool isDestination)
	{
		VkPipelineStageFlags accessMask = 0;

		switch (layout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			if (isDestination)
			{
				LOG("The new layout used in a transition must not be VK_IMAGE_LAYOUT_UNDEFINED.");
			}
			break;

		case VK_IMAGE_LAYOUT_GENERAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT; // VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			accessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			accessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			if (!isDestination)
			{
				accessMask = VK_ACCESS_HOST_WRITE_BIT;
			}
			else
			{
				LOG("The new layout used in a transition must not be VK_IMAGE_LAYOUT_PREINITIALIZED.");
			}
			break;

		case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
			accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			accessMask = VK_ACCESS_MEMORY_READ_BIT;
			break;

		default:
			LOG("Unexpected image layout");
			break;
		}

		return accessMask;
	}

	bool IsDepthFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_D16_UNORM:
		case VK_FORMAT_D32_SFLOAT:
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
		case VK_FORMAT_D24_UNORM_S8_UINT:
		case VK_FORMAT_D16_UNORM_S8_UINT:
			return true;
		}
		return false;
	}

	bool IsStencilFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
		case VK_FORMAT_D24_UNORM_S8_UINT:
			return true;
		}
		return false;
	}

	VkCommandBuffer BeginSingleTimeCommands()
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool();
		allocInfo.commandBufferCount = 1;
		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(VulkanDevice::GetInstance()->GetLogicalDevice(), &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	void EndSingleTimeCommands(VkCommandBuffer commandBuffer)
	{
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo;
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		submitInfo.pSignalSemaphores = nullptr;
		submitInfo.pNext = nullptr;
		submitInfo.pWaitDstStageMask = nullptr;
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.waitSemaphoreCount = 0;

		vkQueueSubmit(VulkanDevice::GetInstance()->GetQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(VulkanDevice::GetInstance()->GetQueue());

		vkFreeCommandBuffers(VulkanDevice::GetInstance()->GetLogicalDevice(),
			VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(), 1, &commandBuffer);
	}
	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldImageLayout, VkImageLayout newImageLayout,
		uint32_t mipLevels, uint32_t layerCount, VkCommandBuffer commandBuffer)
	{

		bool singleTimeCommand = false;

		if (!commandBuffer)
		{
			commandBuffer = BeginSingleTimeCommands();
			singleTimeCommand = true;
		}

		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = IsDepthFormat(format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;

		if (IsStencilFormat(format))
			subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;

		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = mipLevels;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount = layerCount;

		// Create an image barrier object
		VkImageMemoryBarrier imageMemoryBarrier = VkImageMemoryBarrier();
		imageMemoryBarrier.oldLayout = oldImageLayout;
		imageMemoryBarrier.newLayout = newImageLayout;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange = subresourceRange;
		imageMemoryBarrier.srcAccessMask = LayoutToAccessMask(oldImageLayout, false);
		imageMemoryBarrier.dstAccessMask = LayoutToAccessMask(newImageLayout, true);
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		VkPipelineStageFlags sourceStage = 0;
		{
			if (imageMemoryBarrier.oldLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			{
				sourceStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			}
			else if (imageMemoryBarrier.srcAccessMask != 0)
			{
				sourceStage = AccessFlagsToPipelineStage(imageMemoryBarrier.srcAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
			}
			else
			{
				sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			}
		}

		VkPipelineStageFlags destinationStage = 0;
		{
			if (imageMemoryBarrier.newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			{
				destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			}
			else if (imageMemoryBarrier.dstAccessMask != 0)
			{
				destinationStage = AccessFlagsToPipelineStage(imageMemoryBarrier.dstAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
			}
			else
			{
				destinationStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			}
		}

		// Put barrier inside setup command buffer
		vkCmdPipelineBarrier(
			commandBuffer,
			sourceStage,
			destinationStage,
			0,
			0, nullptr,
			0, nullptr,
			1, &imageMemoryBarrier);

		if (singleTimeCommand)
			EndSingleTimeCommands(commandBuffer);
	}
	VulkanSwapChain* VulkanSwapChain::m_ThisInstance = NULL;

	VulkanSwapChain::VulkanSwapChain() :
		m_SwapChainBufferCount(0),
		m_OldSwapChain(0),
		m_CurrentBuffer(0),
		m_Surface(0),
		m_SwapChain(0),
		m_AcquireImageIndex(UINT32_MAX),
		m_ColourFormat(),
		m_ColourSpace()
	{

		
		m_ThisInstance = this;
	}
	VulkanSwapChain::~VulkanSwapChain()
	{
		if (m_SwapChain)
			vkDestroySwapchainKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, 0);

		if (m_Surface)
			vkDestroySurfaceKHR(VulkanContext::GetInstance()->GetVulkanInstance(), m_Surface, 0);
	}

	void VulkanSwapChain::AcquireNextImage()
	{
		VkResult result = vkAcquireNextImageKHR(VulkanDevice::GetInstance()->GetLogicalDevice(),
			m_SwapChain,
			UINT64_MAX,
			m_Frames[m_CurrentBuffer].PresentSemaphore,
			VK_NULL_HANDLE,
			&m_AcquireImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {

			LOG("Acquire Image result : {0}", result == VK_ERROR_OUT_OF_DATE_KHR ? "Out of Date" : "SubOptimal");
			if (result == VK_ERROR_OUT_OF_DATE_KHR)
			{
				OnResize(m_Size);
				return;
			}
		}
		else if (result != VK_SUCCESS)
		{
			LOG("[VULKAN] Failed to acquire swap chain image!");
		}

	}
	void VulkanSwapChain::FindSwapChainFormat()
	{
		u32 objectCount = 0;
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_Surface, &objectCount, 0) != VK_SUCCESS)
			return;

		std::vector<VkSurfaceFormatKHR> surfaceFormats(objectCount);

		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_Surface, &objectCount, surfaceFormats.data()) != VK_SUCCESS)
			return;

		if ((surfaceFormats.size() == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
		{
			m_ColourFormat = VK_FORMAT_B8G8R8A8_UNORM;
			m_ColourSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		}
		else if (!surfaceFormats.empty())
		{
			for (VkSurfaceFormatKHR& surfaceFormat : surfaceFormats)
			{
				if ((surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) &&
					(surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
				{
					m_ColourFormat = VK_FORMAT_B8G8R8A8_UNORM;
					m_ColourSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

					break;
				}
			}

			if (m_ColourFormat == VK_FORMAT_UNDEFINED)
			{
				m_ColourFormat = surfaceFormats[0].format;
				m_ColourSpace = surfaceFormats[0].colorSpace;
			}

		}
		else
			return;
	}
	void VulkanSwapChain::Present(VkSemaphore waitSemaphore)
	{

		VkPresentInfoKHR presentInfo	= VkPresentInfoKHR();
		presentInfo.sType				= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount	= 1;
		presentInfo.pWaitSemaphores		= &waitSemaphore;
		presentInfo.swapchainCount		= 1;
		presentInfo.pSwapchains			= &m_SwapChain;
		presentInfo.pImageIndices		= &m_AcquireImageIndex;

		VkResult result = vkQueuePresentKHR(VulkanDevice::GetInstance()->GetQueue(), &presentInfo);

		if ((result == VK_ERROR_OUT_OF_DATE_KHR))
		{
			LOG("[Vulkan] SwapChain out of date\n");
			return;
		}
		else if (result == VK_SUBOPTIMAL_KHR)
		{
			LOG("[Vulkan] SwapChain suboptimal\n");
			return;
		}
		else if (result != VK_SUCCESS)
			return;
		
	}
	VkImageLayout oldImageLayout = VK_IMAGE_LAYOUT_UNDEFINED, newImageLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	bool VulkanSwapChain::Create(void* platformWindow, const Vector2u & size, bool vsync)
	{
		if (m_Surface == VK_NULL_HANDLE) {
			VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = VkWin32SurfaceCreateInfoKHR();
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
			surfaceCreateInfo.hwnd = static_cast<HWND>(platformWindow);
			if (vkCreateWin32SurfaceKHR(VulkanContext::GetInstance()->GetVulkanInstance(), &surfaceCreateInfo, 0, &m_Surface) != VK_SUCCESS)
				return false;

		}
		bool success = Create(size, vsync);
		AcquireNextImage();
		return true;
	}
	bool VulkanSwapChain::Create(const Vector2u& size, bool vsync)
	{
		m_Size = size;
		FindSwapChainFormat();
		u32 objectCount = 0;
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_Surface, &objectCount, 0) != VK_SUCCESS)
			return false;

		std::vector<VkPresentModeKHR> presentModes(objectCount);
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_Surface, &objectCount, presentModes.data()) != VK_SUCCESS)
			return false;

		VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
		if (vsync)
		{
			for (VkPresentModeKHR& i : presentModes)
			{
				if (i == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					presentMode = i;
					break;
				}
				else if (i == VK_PRESENT_MODE_FIFO_KHR)
				{
					presentMode = i;
					break;
				}
				else if (i == VK_PRESENT_MODE_IMMEDIATE_KHR)
				{
					presentMode = i;
					break;
				}
			}
		}

		VkSurfaceCapabilitiesKHR surfaceCapabilities;

		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_Surface, &surfaceCapabilities) != VK_SUCCESS)
			return false;


		VkExtent2D m_SwapchainExtent;
		m_SwapchainExtent.width = std::clamp<u32>(size.x,
			surfaceCapabilities.minImageExtent.width,
			surfaceCapabilities.maxImageExtent.width);
		m_SwapchainExtent.height = std::clamp<u32>(size.y,
			surfaceCapabilities.minImageExtent.height,
			surfaceCapabilities.maxImageExtent.height);

		VkSurfaceTransformFlagBitsKHR preTransform;
		if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		else
			preTransform = surfaceCapabilities.currentTransform;

		m_SwapChainBufferCount = surfaceCapabilities.maxImageCount;
		if (m_SwapChainBufferCount > 3)
			m_SwapChainBufferCount = 3;
		VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		};
		for (auto& compositeAlphaFlag : compositeAlphaFlags)
		{
			if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlag)
			{
				compositeAlpha = compositeAlphaFlag;
				break;
			};
		}
		VkSwapchainCreateInfoKHR swapchainCreateInfo = VkSwapchainCreateInfoKHR();
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface = m_Surface;
		swapchainCreateInfo.minImageCount = m_SwapChainBufferCount;
		swapchainCreateInfo.imageFormat = m_ColourFormat;
		swapchainCreateInfo.imageColorSpace = m_ColourSpace;
		swapchainCreateInfo.imageExtent = m_SwapchainExtent;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCreateInfo.preTransform = preTransform;
		swapchainCreateInfo.compositeAlpha = compositeAlpha;
		swapchainCreateInfo.presentMode = presentMode;
		swapchainCreateInfo.clipped = 1;
		swapchainCreateInfo.oldSwapchain = m_OldSwapChain;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

		if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
			swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

		if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
			swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;


		if (vkCreateSwapchainKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), &swapchainCreateInfo, 0, &m_SwapChain) != VK_SUCCESS)
			return false;


		/**if (m_OldSwapChain != VK_NULL_HANDLE)
		{
			for (u32 i = 0; i < m_SwapChainBufferCount; i++)
			{
				if (m_Frames[i].CommandBuffer->GetState() == CommandBufferState::Submitted)
					m_Frames[i].CommandBuffer->Wait();

				m_Frames[i].CommandBuffer->Reset();

				delete m_SwapChainBuffers[i];
				vkDestroySemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Frames[i].PresentSemaphore, nullptr);
				m_Frames[i].PresentSemaphore = VK_NULL_HANDLE;
			}

			m_SwapChainBuffers.clear();

			vkDestroySwapchainKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_OldSwapChain, VK_NULL_HANDLE);
			m_OldSwapChain = VK_NULL_HANDLE;
		}*/
		objectCount = 0;
		if (vkGetSwapchainImagesKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, &objectCount, 0) != VK_SUCCESS)
			return false;


		std::vector<VkImage> m_SwapchainImages(objectCount);

		if (vkGetSwapchainImagesKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, &objectCount, m_SwapchainImages.data()) != VK_SUCCESS)
			return false;



		VkImageViewCreateInfo imageViewCreateInfo = VkImageViewCreateInfo();
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = m_ColourFormat;
		imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
		imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;

		for (u32 i = 0; i < m_SwapChainBufferCount; ++i)
		{
			VkImageView imageView;
			imageViewCreateInfo.image = m_SwapchainImages[i];
			if (vkCreateImageView(VulkanDevice::GetInstance()->GetLogicalDevice(), &imageViewCreateInfo, 0, &imageView) != VK_SUCCESS)
				return false;
			if (oldImageLayout != newImageLayout)
				TransitionImageLayout(m_SwapchainImages[i], m_ColourFormat, oldImageLayout, newImageLayout, 1, 1, NULL);

			oldImageLayout = newImageLayout;
		}

		return true;
	}

	void VulkanSwapChain::OnResize(const Vector2u& size, void* window)
	{
		VulkanDevice::GetInstance()->WaitIdle();
		m_OldSwapChain = m_SwapChain;
		m_SwapChain = NULL;
		m_Size = size;
		if (window)
			Create(window, size, true);
		else
			Create(size, true);

		VulkanDevice::GetInstance()->WaitIdle();
	}
	void VulkanSwapChain::Begin()
	{
		m_CurrentBuffer = (m_CurrentBuffer + 1) % m_SwapChainBufferCount;

		auto commandBuffer = m_Frames[m_CurrentBuffer].CommandBuffer;
		if (commandBuffer->GetState() == CommandBufferState::Submitted)
			if (!commandBuffer->Wait())
				return;
		commandBuffer->Reset();
		AcquireNextImage();
		commandBuffer->Begin();
	}
	void VulkanSwapChain::QueueSubmit()
	{
		m_Frames[m_CurrentBuffer].CommandBuffer->Submit(VulkanDevice::GetInstance()->GetQueue(), m_Frames[m_CurrentBuffer].PresentSemaphore);
	}
	void VulkanSwapChain::End()
	{
		m_Frames[m_CurrentBuffer].CommandBuffer->End();
	}
	FrameData& VulkanSwapChain::GetCurrentFrameData()
	{
		return m_Frames[m_CurrentBuffer];
	}
	void VulkanSwapChain::CreateFrameData()
	{
		for (u32 i = 0; i < m_SwapChainBufferCount; i++)
		{

			VkSemaphoreCreateInfo semaphoreCreateInfo = VkSemaphoreCreateInfo();
			semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			if (m_Frames[i].PresentSemaphore == NULL)
				vkCreateSemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), &semaphoreCreateInfo, 0, &m_Frames[i].PresentSemaphore);
			

			if (!m_Frames[i].CommandBuffer)
			{
				m_Frames[i].CommandPool = new VulkanCommandPool();
				m_Frames[i].CommandPool->Create(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetQueueFamilyIndex());


				m_Frames[i].CommandBuffer = new VulkanCommandBuffer();
				m_Frames[i].CommandBuffer->Create(VulkanDevice::GetInstance()->GetLogicalDevice(), true, m_Frames[i].CommandPool->GetCommandPool());

			}
		}
	}
}

