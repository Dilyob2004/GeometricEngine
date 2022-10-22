#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <Engine/Render/Vulkan/VkRenderPass.h>

namespace MeteorEngine
{
	VulkanFrameBuffer* VulkanFrameBuffer::thisInstance = NULL;
	VulkanFrameBuffer::VulkanFrameBuffer(const FrameBufferDesc& desc):
		m_Framebuffers(0),
		m_FrameBufferDesc(desc)
	{
		thisInstance = this;
		m_AttachmentCount = desc.AttachmentCount;
		m_Size = desc.Size;

		std::vector<VkImageView> attachments;
		for (u32 i = 0; i < m_AttachmentCount; i++)
		{
			if (desc.AttachmentTypes[i] == TextureType::COLOR)
				attachments.emplace_back(dynamic_cast<VulkanTexture2D*>(desc.Attachments[i])->GetImageView());
			else if(desc.AttachmentTypes[i] == TextureType::DEPTH)
				attachments.emplace_back(dynamic_cast<VulkanTextureDepth*>(desc.Attachments[i])->GetImageView());
		}
		VkFramebufferCreateInfo framebufferCreateInfo = VkFramebufferCreateInfo();
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass = dynamic_cast<VulkanRenderPass*>(desc.RenderPass)->GetRenderPass();
		framebufferCreateInfo.pAttachments = attachments.data();
		framebufferCreateInfo.attachmentCount = m_AttachmentCount;
		framebufferCreateInfo.width = m_Size.x;
		framebufferCreateInfo.height = m_Size.y;
		framebufferCreateInfo.layers = 1;
		if (vkCreateFramebuffer(VulkanDevice::GetInstance()->GetLogicalDevice(), &framebufferCreateInfo, 0, &m_Framebuffers) != VK_SUCCESS)
			LOG("[Vulkan] Failed to Create a Framebuffer");
	}
	VulkanFrameBuffer::~VulkanFrameBuffer()
	{
		if (m_Framebuffers)
			vkDestroyFramebuffer(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Framebuffers, 0);
	}
}