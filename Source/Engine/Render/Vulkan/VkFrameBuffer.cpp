#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkContext.h>
#define VCI VulkanContext::GetInstance()
#define VDI VulkanDevice::GetInstance()
#define VSI VulkanSwapChain::GetInstance()

namespace MeteorEngine
{
	VulkanFrameBuffer* VulkanFrameBuffer::thisInstance = NULL;
	VulkanFrameBuffer::VulkanFrameBuffer():
		m_SwapchainFramebuffers()
	{
		thisInstance = this;
	}
	VulkanFrameBuffer::~VulkanFrameBuffer()
	{

	}
	bool VulkanFrameBuffer::CreateFrameBuffer(u32 width, u32 height)
	{
		VkRenderPass renderPass = 0; VkImage depthImage = 0;
		VkImageView depthImageView = 0;
		VkDeviceMemory depthImageMemory = 0;
	/**
		// Create our depth image
		if (!VulkanTexture::CreateImage(width,
			height,
			VDI->GetSupportDepthFormat(),
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			depthImage,
			depthImageMemory))
			return false;
		// Allocate a command buffer
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = VkCommandBufferAllocateInfo();
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandPool = VCI->GetCommandPool();
		commandBufferAllocateInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;

		if (vkAllocateCommandBuffers(VDI->GetLogicalDevice(), &commandBufferAllocateInfo, &commandBuffer) != VK_SUCCESS)
			return false;
		
		// Begin the command buffer
		VkCommandBufferBeginInfo commandBufferBeginInfo = VkCommandBufferBeginInfo();
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VkSubmitInfo submitInfo = VkSubmitInfo();
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		if (vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
		{
			vkFreeCommandBuffers(VDI->GetLogicalDevice(), VCI->GetCommandPool(), 1, &commandBuffer);
			return false;
		}

		// Submit a barrier to transition the image layout to depth stencil optimal
		VkImageMemoryBarrier barrier = VkImageMemoryBarrier();
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		barrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = depthImage;
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT |
			((VDI->GetSupportDepthFormat() == VK_FORMAT_D32_SFLOAT) ? 0 : VK_IMAGE_ASPECT_STENCIL_BIT);
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		vkCmdPipelineBarrier(commandBuffer,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
			VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
			0,
			0,
			0,
			0,
			0,
			1,
			&barrier);

		// End and subm0it the command buffer
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
		{
			vkFreeCommandBuffers(VDI->GetLogicalDevice(), VCI->GetCommandPool(), 1, &commandBuffer);
			return false;
		}

		if (vkQueueSubmit(VDI->GetQueue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
		{
			vkFreeCommandBuffers(VDI->GetLogicalDevice(), VCI->GetCommandPool(), 1, &commandBuffer);
			return false;
		}

		// Ensure the command buffer has been processed
		if (vkQueueWaitIdle(VDI->GetQueue()) != VK_SUCCESS)
		{
			vkFreeCommandBuffers(VDI->GetLogicalDevice(), VCI->GetCommandPool(), 1, &commandBuffer);
			return false;
		}

		// Free the command buffer
		vkFreeCommandBuffers(VDI->GetLogicalDevice(), VCI->GetCommandPool(), 1, &commandBuffer);



		VkImageViewCreateInfo imageViewCreateInfo = VkImageViewCreateInfo();
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.image = depthImage;
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = VDI->GetSupportDepthFormat();
		imageViewCreateInfo.subresourceRange
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT |
			((VDI->GetSupportDepthFormat() == VK_FORMAT_D32_SFLOAT) ? 0 : VK_IMAGE_ASPECT_STENCIL_BIT);
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;


		// Create the depth image view
		if (vkCreateImageView(VDI->GetLogicalDevice(), &imageViewCreateInfo, 0, &depthImageView) != VK_SUCCESS)
		{
			return false;
		}


		VkAttachmentDescription attachmentDescriptions[2];
		// Color attachment
		attachmentDescriptions[0] = VkAttachmentDescription();
		attachmentDescriptions[0].format = VSI->GetSwapChainFormat();
		attachmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		// Depth attachment
		attachmentDescriptions[1] = VkAttachmentDescription();
		attachmentDescriptions[1].format = VDI->GetSupportDepthFormat();
		attachmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDescriptions[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDescriptions[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference colorAttachmentReference = {};
		colorAttachmentReference.attachment = 0;
		colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthStencilAttachmentReference = {};
		depthStencilAttachmentReference.attachment = 1;
		depthStencilAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		// Set up the renderpass to depend on commands that execute before the renderpass begins
		VkSubpassDescription subpassDescription = VkSubpassDescription();
		subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &colorAttachmentReference;
		subpassDescription.pDepthStencilAttachment = &depthStencilAttachmentReference;

		VkSubpassDependency subpassDependency = VkSubpassDependency();
		subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpassDependency.srcAccessMask = 0;
		subpassDependency.dstSubpass = 0;
		subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassCreateInfo = VkRenderPassCreateInfo();
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = 2;
		renderPassCreateInfo.pAttachments = attachmentDescriptions;
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpassDescription;
		renderPassCreateInfo.dependencyCount = 1;
		renderPassCreateInfo.pDependencies = &subpassDependency;

		// Create the renderpass
		if (vkCreateRenderPass(VDI->GetLogicalDevice(), &renderPassCreateInfo, 0, &renderPass) != VK_SUCCESS)
			return false;*/
		std::vector<VkImageView> swapChainImageViews(VSI->GetSwapChainImageViews());
		m_SwapchainFramebuffers.resize(swapChainImageViews.size());
		VkFramebufferCreateInfo framebufferCreateInfo = VkFramebufferCreateInfo();
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass = renderPass;
		framebufferCreateInfo.attachmentCount = 2;
		framebufferCreateInfo.width = width;
		framebufferCreateInfo.height = height;
		framebufferCreateInfo.layers = 1;

		for (u32 i = 0; i < m_SwapchainFramebuffers.size(); ++i)
		{
			// Each framebuffer consists of a corresponding swapchain image and the shared depth image
			VkImageView attachments[] = { swapChainImageViews[i], depthImageView };
			framebufferCreateInfo.pAttachments = attachments;

			// Create the framebuffer
			if (vkCreateFramebuffer(VDI->GetLogicalDevice(), &framebufferCreateInfo, 0, &m_SwapchainFramebuffers[i]) != VK_SUCCESS) 
				return false;
			
		}
		return true;
	}
}