
#include <Engine/Render/Vulkan/VkSwapChain.h> 
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <cassert>
namespace MeteorEngine
{

	VulkanSwapChain* VulkanSwapChain::m_ThisInstance = NULL;

	VulkanSwapChain::VulkanSwapChain() :
		m_ContextWindow(0),
		m_SwapChainBufferCount(0),
		m_OldSwapChain(0),
		m_CurrentBuffer(0),
		m_SwapChain(0),
		m_AcquireImageIndex(UINT32_MAX),
		m_ColourFormat(),
		m_ColourSpace()
	{

		
		m_ThisInstance = this;
	}

	VulkanSwapChain::VulkanSwapChain(VulkanContext* context, const Vector2u& size, bool vsync) :
		m_ContextWindow(0),
		m_SwapChainBufferCount(0),
		m_OldSwapChain(0),
		m_CurrentBuffer(0),
		m_SwapChain(0),
		m_AcquireImageIndex(UINT32_MAX),
		m_ColourFormat(),
		m_ColourSpace()
	{
		Create(context, size, vsync);
	}
	VulkanSwapChain::~VulkanSwapChain()	
	{
		if (m_SwapChain)
			vkDestroySwapchainKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, 0);

		if (m_ContextWindow->GetSurface())
			vkDestroySurfaceKHR(VulkanContext::GetInstance()->GetVulkanInstance(), m_ContextWindow->GetSurface(), 0);
	}

	void VulkanSwapChain::AcquireNextImage()
	{
		if (m_SwapChain) {
				VkResult result = vkAcquireNextImageKHR(VulkanDevice::GetInstance()->GetLogicalDevice(),
					m_SwapChain,
					UINT64_MAX,
					m_FramesBackBuffer[m_CurrentBuffer].PresentSemaphore,
					VK_NULL_HANDLE,
					&m_AcquireImageIndex);
			if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {

				LOG("[Vulkan] Acquire Image result : 0 ");
				LOG( ((result == VK_ERROR_OUT_OF_DATE_KHR) ? "Out of Date" : "SubOptimal") );
				if (result == VK_ERROR_OUT_OF_DATE_KHR)
				{
					Resize(m_Size);
					return;
				}
			}
			else if (result != VK_SUCCESS)
			{
				LOG("[Vulkan] Failed to acquire swap chain image!");
			}
		}
		return;

	}
	void VulkanSwapChain::FindSwapChainFormat()
	{
		u32 objectCount = 0;
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_ContextWindow->GetSurface(), &objectCount, 0) != VK_SUCCESS)
			return;
		
		std::vector<VkSurfaceFormatKHR> surfaceFormats(objectCount);

		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_ContextWindow->GetSurface(), &objectCount, surfaceFormats.data()) != VK_SUCCESS)
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
	void VulkanSwapChain::Present()
	{
		VkSemaphore waitSemaphore = GetCurrentBackBuffer().CommandBuffer->GetSemaphore();
		if (m_SwapChain) 
		{
			VkPresentInfoKHR presentInfo = VkPresentInfoKHR();
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = &waitSemaphore;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = &m_SwapChain;
			presentInfo.pImageIndices = &m_AcquireImageIndex;

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
	}
	bool VulkanSwapChain::Create(VulkanContext* context, const Vector2u & size, bool vsync)
	{
		m_ContextWindow = context;
		bool success = Create(size, vsync);
		AcquireNextImage();
		return success;
	}
	bool VulkanSwapChain::Create(const Vector2u& size, bool vsync)
	{
		m_Size = size;
		FindSwapChainFormat();
		u32 objectCount = 0;
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_ContextWindow->GetSurface(), &objectCount, 0) != VK_SUCCESS)
			return false;

		std::vector<VkPresentModeKHR> presentModes(objectCount);
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_ContextWindow->GetSurface(), &objectCount, presentModes.data()) != VK_SUCCESS)
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

		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VulkanDevice::GetInstance()->GetPhysicalDevice(), m_ContextWindow->GetSurface(), &surfaceCapabilities) != VK_SUCCESS)
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
		swapchainCreateInfo.surface = m_ContextWindow->GetSurface();
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


		if (m_OldSwapChain != VK_NULL_HANDLE)
		{
			for (u32 i = 0; i < m_SwapChainBufferCount; i++)
			{
				if (m_FramesBackBuffer[i].CommandBuffer->GetState() == CommandBufferState::Submitted)
					m_FramesBackBuffer[i].CommandBuffer->Wait();

				m_FramesBackBuffer[i].CommandBuffer->Reset();

				delete m_SwapChainBuffers[i];
				vkDestroySemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), m_FramesBackBuffer[i].PresentSemaphore, nullptr);
				m_FramesBackBuffer[i].PresentSemaphore = VK_NULL_HANDLE;
			}

			m_SwapChainBuffers.clear();

			vkDestroySwapchainKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_OldSwapChain, VK_NULL_HANDLE);
			m_OldSwapChain = VK_NULL_HANDLE;
		}
		{
			u32 imageCount = 0;
			if (vkGetSwapchainImagesKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, &imageCount, 0) != VK_SUCCESS)
				return false;


			std::vector<VkImage> m_SwapchainImages(imageCount);

			if (vkGetSwapchainImagesKHR(VulkanDevice::GetInstance()->GetLogicalDevice(), m_SwapChain, &imageCount, m_SwapchainImages.data()) != VK_SUCCESS)
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

				VulkanTexture2D* swapChainBuffer = new VulkanTexture2D(m_SwapchainImages[i], imageView, m_ColourFormat, size);
				swapChainBuffer->TransitionImage(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

				m_SwapChainBuffers.emplace_back(swapChainBuffer);
			}
			m_SwapchainImages.clear();
		}
		CreateFrameData();
		return true;
	}
	void VulkanSwapChain::Resize(const Vector2u& size)
	{
		VulkanDevice::GetInstance()->WaitIdle();
		m_OldSwapChain = m_SwapChain;
		m_SwapChain = NULL;
		m_Size = size;
		if (m_ContextWindow)
			Create(m_ContextWindow, size, true);
		else
			Create(size, true);

		VulkanDevice::GetInstance()->WaitIdle();
	}
	void VulkanSwapChain::Begin()
	{
		m_CurrentBuffer = (m_CurrentBuffer + 1) % m_SwapChainBufferCount;

		auto commandBuffer = m_FramesBackBuffer[m_CurrentBuffer].CommandBuffer;
		if (commandBuffer->GetState() == CommandBufferState::Submitted)
			if (!commandBuffer->Wait())
				return;
		commandBuffer->Reset();
		AcquireNextImage();
		commandBuffer->Begin();
	}
	void VulkanSwapChain::QueueSubmit()
	{
		m_FramesBackBuffer[m_CurrentBuffer].CommandBuffer->Submit(m_FramesBackBuffer[m_CurrentBuffer].PresentSemaphore);
	}
	void VulkanSwapChain::End()
	{
		m_FramesBackBuffer[m_CurrentBuffer].CommandBuffer->End();
	}
	VulkanBackBuffer& VulkanSwapChain::GetCurrentBackBuffer()
	{
		return m_FramesBackBuffer[m_CurrentBuffer];
	}
	void VulkanSwapChain::CreateFrameData()
	{
		for (u32 i = 0; i < m_SwapChainBufferCount; i++)
		{

			VkSemaphoreCreateInfo semaphoreCreateInfo = VkSemaphoreCreateInfo();
			semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			if (m_FramesBackBuffer[i].PresentSemaphore == NULL)
				vkCreateSemaphore(VulkanDevice::GetInstance()->GetLogicalDevice(), &semaphoreCreateInfo, 0, &m_FramesBackBuffer[i].PresentSemaphore);
			

			if (!m_FramesBackBuffer[i].CommandBuffer)
			{
				m_FramesBackBuffer[i].CommandPool = new VulkanCommandPool();
				m_FramesBackBuffer[i].CommandPool->Create(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetQueueFamilyIndex());


				m_FramesBackBuffer[i].CommandBuffer = new VulkanCommandBuffer();
				m_FramesBackBuffer[i].CommandBuffer->Init(true, m_FramesBackBuffer[i].CommandPool->GetCommandPool());

			}
		}
	}
}

