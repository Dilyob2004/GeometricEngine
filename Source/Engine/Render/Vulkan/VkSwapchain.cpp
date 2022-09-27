#include <Engine/Render/Vulkan/VkSwapchain.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <cassert>
#define	VKDI VulkanDevice::GetInstance()
namespace MeteorEngine
{
	VulkanSwapChain* VulkanSwapChain::thisInstance = NULL;

	VulkanSwapChain::VulkanSwapChain():
		m_SwapChain(0),
		m_SwapchainFormat(),
		m_SwapchainImages(),
		m_SwapchainImageViews()
	{
		thisInstance = this;
	}
	VulkanSwapChain::~VulkanSwapChain()
	{

	}
	bool VulkanSwapChain::CreateSwapChain(u32 width, u32 height)
	{

		// Select a surface format that supports RGBA color format
		std::uint32_t objectCount = 0;

		std::vector<VkSurfaceFormatKHR> surfaceFormats;

		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VKDI->GetPhysicalDevice(), VKDI->GetSurface(), &objectCount, 0) != VK_SUCCESS)
			return false;

		surfaceFormats.resize(objectCount);

		if (vkGetPhysicalDeviceSurfaceFormatsKHR(VKDI->GetPhysicalDevice(), VKDI->GetSurface(), &objectCount, surfaceFormats.data()) != VK_SUCCESS)
			return false;

		if ((surfaceFormats.size() == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
		{
			m_SwapchainFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
			m_SwapchainFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		}
		else if (!surfaceFormats.empty())
		{
			for (VkSurfaceFormatKHR& surfaceFormat : surfaceFormats)
			{
				if ((surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) &&
					(surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
				{
					m_SwapchainFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
					m_SwapchainFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

					break;
				}
			}

			if (m_SwapchainFormat.format == VK_FORMAT_UNDEFINED)
				m_SwapchainFormat = surfaceFormats[0];
		}
		else
			return false;

		// Select a swapchain present mode
		std::vector<VkPresentModeKHR> presentModes;

		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VKDI->GetPhysicalDevice(), VKDI->GetSurface(), &objectCount, 0) != VK_SUCCESS)
			return false;

		presentModes.resize(objectCount);

		if (vkGetPhysicalDeviceSurfacePresentModesKHR(VKDI->GetPhysicalDevice(), VKDI->GetSurface(), &objectCount, presentModes.data()) != VK_SUCCESS)
			return false;

		// Prefer mailbox over FIFO if it is available
		VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

		for (VkPresentModeKHR& i : presentModes)
		{
			if (i == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				presentMode = i;
				break;
			}
		}

		// Determine size and count of swapchain images
		VkSurfaceCapabilitiesKHR surfaceCapabilities;

		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VKDI->GetPhysicalDevice(), VKDI->GetSurface(), &surfaceCapabilities) != VK_SUCCESS)
			return false;
		

		VkExtent2D m_SwapchainExtent;
		m_SwapchainExtent.width = std::clamp<u32>(width,
			surfaceCapabilities.minImageExtent.width,
			surfaceCapabilities.maxImageExtent.width);
		m_SwapchainExtent.height = std::clamp<u32>(height,
			surfaceCapabilities.minImageExtent.height,
			surfaceCapabilities.maxImageExtent.height);

		auto imageCount = std::clamp<u32>(2, surfaceCapabilities.minImageCount, surfaceCapabilities.maxImageCount);

		VkSwapchainCreateInfoKHR swapchainCreateInfo	= VkSwapchainCreateInfoKHR();
		swapchainCreateInfo.sType						= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.surface						= VKDI->GetSurface();
		swapchainCreateInfo.minImageCount				= imageCount;
		swapchainCreateInfo.imageFormat					= m_SwapchainFormat.format;
		swapchainCreateInfo.imageColorSpace				= m_SwapchainFormat.colorSpace;
		swapchainCreateInfo.imageExtent					= m_SwapchainExtent;
		swapchainCreateInfo.imageArrayLayers			= 1;
		swapchainCreateInfo.imageUsage					= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCreateInfo.imageSharingMode			= VK_SHARING_MODE_EXCLUSIVE;
		swapchainCreateInfo.preTransform				= surfaceCapabilities.currentTransform;
		swapchainCreateInfo.compositeAlpha				= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.presentMode					= presentMode;
		swapchainCreateInfo.clipped						= VK_TRUE;
		swapchainCreateInfo.oldSwapchain				= VK_NULL_HANDLE;

		// Create the swapchain
		if (vkCreateSwapchainKHR(VKDI->GetLogicalDevice(), &swapchainCreateInfo, 0, &m_SwapChain) != VK_SUCCESS)
			return false;

		//Swap Chain Image Views
		objectCount = 0;

		if (vkGetSwapchainImagesKHR(VKDI->GetLogicalDevice(), m_SwapChain, &objectCount, 0) != VK_SUCCESS)
			return false;
		

		m_SwapchainImages.resize(objectCount);
		m_SwapchainImageViews.resize(objectCount);

		if (vkGetSwapchainImagesKHR(VKDI->GetLogicalDevice(), m_SwapChain, &objectCount, m_SwapchainImages.data()) != VK_SUCCESS)
			return false;



		VkImageViewCreateInfo imageViewCreateInfo			= VkImageViewCreateInfo();
		imageViewCreateInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.viewType						= VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format							= m_SwapchainFormat.format;
		imageViewCreateInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCreateInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCreateInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCreateInfo.components.a					= VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCreateInfo.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.baseMipLevel	= 0;
		imageViewCreateInfo.subresourceRange.levelCount		= 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer	= 0;
		imageViewCreateInfo.subresourceRange.layerCount		= 1;


		//return VulkanTexture::CreateImageViews(imageViewCreateInfo, m_SwapchainImages, m_SwapchainImageViews);
		// Create an image view for each swapchain image
		for (std::size_t i = 0; i < m_SwapchainImages.size(); ++i)
		{
			imageViewCreateInfo.image = m_SwapchainImages[i];

			if (vkCreateImageView(VKDI->GetLogicalDevice(), &imageViewCreateInfo, 0, &m_SwapchainImageViews[i]) != VK_SUCCESS)
				return false;
		}


		return true;
	}
}

