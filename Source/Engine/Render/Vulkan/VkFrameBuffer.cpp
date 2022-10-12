#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkContext.h>

namespace MeteorEngine
{
	VulkanFrameBuffer* VulkanFrameBuffer::thisInstance = NULL;
	VulkanFrameBuffer::VulkanFrameBuffer():
		m_SwapchainFramebuffers(0),
		m_Device(0),
		m_AttachmentCount(0)
	{
		thisInstance = this;
	}
	VulkanFrameBuffer::~VulkanFrameBuffer()
	{
		if (m_SwapchainFramebuffers)
			vkDestroyFramebuffer(m_Device, m_SwapchainFramebuffers, 0);
	}
	bool VulkanFrameBuffer::Create(VkDevice device, VkRenderPass renderPass, std::vector<VkImageView> attachments, const Vector2u& size)
	{
		m_Device = device;
		m_AttachmentCount = attachments.size();
		VkFramebufferCreateInfo framebufferCreateInfo	= VkFramebufferCreateInfo();
		framebufferCreateInfo.sType						= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass				= renderPass;
		framebufferCreateInfo.pAttachments				= attachments.data();
		framebufferCreateInfo.attachmentCount			= m_AttachmentCount;
		framebufferCreateInfo.width						= size.x;
		framebufferCreateInfo.height					= size.y;
		framebufferCreateInfo.layers					= 1;
		if (vkCreateFramebuffer(device, &framebufferCreateInfo, 0, &m_SwapchainFramebuffers) != VK_SUCCESS)
			return false;

		return true;
	}
}