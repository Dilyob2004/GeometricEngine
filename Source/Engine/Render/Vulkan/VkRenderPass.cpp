#include <Engine/Render/Vulkan/VkRenderPass.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <vector>

namespace MeteorEngine
{
	VulkanRenderPass::VulkanRenderPass(const RenderPassDesc& desc)
	{
		Init(desc);
	}
	VulkanRenderPass::~VulkanRenderPass()
	{

	}
	VkAttachmentDescription GetAttachmentDescription(TextureType type, Texture* texture, bool clear = true)
	{
		VkAttachmentDescription attachment = VkAttachmentDescription();
		switch (type)
		{
			case TextureType::COLOR:
				VulkanTexture2D* colourTexture = ((VulkanTexture2D*)texture);
				attachment.format = colourTexture->GetVKFormat();
				attachment.initialLayout = colourTexture->GetImageLayout();
				attachment.finalLayout = attachment.initialLayout;
			break;
			case TextureType::DEPTH:
				attachment.format = ((VulkanTextureDepth*)texture)->GetVKFormat();
				attachment.initialLayout = ((VulkanTextureDepth*)texture)->GetImageLayout();
				attachment.finalLayout = attachment.initialLayout;
				break;
			default:
				LOG("[Vulkan] - Unsupported TextureType - {0}", static_cast<int>(type));
				return attachment;
				break;
		}
		if (clear)
		{
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}
		else
		{
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		}

		attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.flags = 0;

		return attachment;
	}
	bool VulkanRenderPass::Init(const RenderPassDesc& desc)
	{
		std::vector<VkAttachmentDescription> attachments;
		std::vector<VkAttachmentReference> colorAttachmentReferences, depthAttachmentReferences;
		for (u32 i = 0; i < desc.AttachmentCount; i++)
		{
			attachments.emplace_back(GetAttachmentDescription(desc.AttachmentTypes[i], desc.Attachments[i], desc.Clear));

			if (desc.AttachmentTypes[i] == TextureType::COLOR)
			{
				VkImageLayout layout = ((VulkanTexture2D*)desc.Attachments[i])->GetImageLayout();
				VkAttachmentReference colorAttachmentRef = VkAttachmentReference();
				colorAttachmentRef.attachment = u32(i);
				colorAttachmentRef.layout = (layout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR) ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL : layout;
				colorAttachmentReferences.push_back(colorAttachmentRef);
				m_DepthOnly = false;
			}
			else if (desc.AttachmentTypes[i] == TextureType::DEPTH)
			{
				VkAttachmentReference depthAttachmentRef = {};
				depthAttachmentRef.attachment = uint32_t(i);
				depthAttachmentRef.layout = ((VulkanTextureDepth*)desc.Attachments[i])->GetImageLayout();
				depthAttachmentReferences.push_back(depthAttachmentRef);
				m_ClearDepth = desc.Clear;
			}
		}

		VkSubpassDescription subpass = VkSubpassDescription();
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount	= static_cast<u32>(colorAttachmentReferences.size());
		subpass.pColorAttachments = colorAttachmentReferences.data();
		subpass.pDepthStencilAttachment = depthAttachmentReferences.data();

		m_ColorAttachmentCount = s32(colorAttachmentReferences.size());

		VkRenderPassCreateInfo renderPassCreateInfo = VkRenderPassCreateInfo();
		renderPassCreateInfo.attachmentCount = u32(desc.AttachmentCount);
		renderPassCreateInfo.pAttachments = attachments.data();
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpass;
		renderPassCreateInfo.dependencyCount = 0;
		renderPassCreateInfo.pDependencies = nullptr;

		if (vkCreateRenderPass(VulkanDevice::GetInstance()->GetLogicalDevice(), &renderPassCreateInfo, VK_NULL_HANDLE, &m_RenderPass) != VK_SUCCESS)
			return false;

		m_ClearValue = new VkClearValue[desc.AttachmentCount];
		m_ClearCount = desc.AttachmentCount;
		m_SwapChainTarget = desc.SwapChainTarget;

	}
	VkSubpassContents SubPassContentsToVK(SubPassContents contents)
	{
		switch (contents)
		{
		case INLINE:
			return VK_SUBPASS_CONTENTS_INLINE;
		case SECONDARY:
			return VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
		default:
			return VK_SUBPASS_CONTENTS_INLINE;
		}
	}
	void VulkanRenderPass::BeginRenderpass(CommandBuffer* commandBuffer, float* clearColour, FrameBuffer* frame, SubPassContents contents, const Vector2u& size) const
	{
		if (!m_DepthOnly)
			for (int i = 0; i < m_ClearCount; i++)
			{
				m_ClearValue[i].color.float32[0] = clearColour[0];
				m_ClearValue[i].color.float32[1] = clearColour[1];
				m_ClearValue[i].color.float32[2] = clearColour[2];
				m_ClearValue[i].color.float32[3] = clearColour[3];
			}

		if (m_ClearDepth)
			m_ClearValue[m_ClearCount - 1].depthStencil = VkClearDepthStencilValue{ 1.0f, 0 };

		VkRenderPassBeginInfo rpBegin = VkRenderPassBeginInfo();
		rpBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rpBegin.pNext = NULL;
		rpBegin.renderPass = m_RenderPass;
		rpBegin.framebuffer = dynamic_cast<VulkanFrameBuffer*>(frame)->GetFrameBuffer();
		rpBegin.renderArea.offset.x = 0;
		rpBegin.renderArea.offset.y = 0;
		rpBegin.renderArea.extent.width = size.x;
		rpBegin.renderArea.extent.height = size.y;
		rpBegin.clearValueCount = u32(m_ClearCount);
		rpBegin.pClearValues = m_ClearValue;

		vkCmdBeginRenderPass(dynamic_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), &rpBegin, SubPassContentsToVK(contents));
		commandBuffer->UpdateViewport(size, m_SwapChainTarget);
	}

	void VulkanRenderPass::EndRenderpass(CommandBuffer* commandBuffer)
	{
		vkCmdEndRenderPass(dynamic_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer());
	}
}