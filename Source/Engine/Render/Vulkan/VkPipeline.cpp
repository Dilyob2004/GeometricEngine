#include <Engine/Render/Vulkan/VkPipeline.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>

namespace MeteorEngine
{
	VulkanPipeline::VulkanPipeline():
		m_PipelineInfo(),
		m_RenderPass(NULL),
		m_FrameBuffer()
	{

	}
	VulkanPipeline::VulkanPipeline(const PipelineInfo& pipelineInfo):
		m_PipelineInfo(pipelineInfo),
		m_RenderPass(NULL),
		m_FrameBuffer()
	{
		PreInit();
	}
	VulkanPipeline::~VulkanPipeline()
	{

	}
	void VulkanPipeline::Begin(CommandBuffer* commandBuffer, u32 layer)
	{
		FrameBuffer* frameBuffer;
		if (true)
		{
			TransitionBackbuffers();
			if (m_PipelineInfo.SwapChainTarget)
				frameBuffer = m_FrameBuffer[RendererCommand::GetMainSwapChain()->GetCurrentImageIndex()];
			else
				frameBuffer = m_FrameBuffer[0];

			m_RenderPass->BeginRenderpass(commandBuffer, m_PipelineInfo.clearColor, frameBuffer, SubPassContents::INLINE, { 1000, 1000 });

		}
		else
		{
			commandBuffer->UpdateViewport({ 1000, 1000 }, false);
		}

	}
	void VulkanPipeline::End(CommandBuffer* commandBuffer)
	{
		m_RenderPass->EndRenderpass(commandBuffer);
	}

	void VulkanPipeline::PreInit()
	{
		std::vector<Texture*> attachments;
		std::vector<TextureType> attachmentTypes;
		if (m_PipelineInfo.SwapChainTarget)
		{
			attachments.push_back(RendererCommand::GetMainSwapChain()->GetImage(0));
			attachmentTypes.push_back(TextureType::COLOR);
		}
		else
			for (auto texture : m_PipelineInfo.ColorTargets)
				if (texture)
				{
					attachments.push_back(texture);
					attachmentTypes.push_back(texture->GetType());
				}

		if (m_PipelineInfo.DepthTarget)
		{
			attachments.push_back(m_PipelineInfo.DepthTarget);
			attachmentTypes.push_back(TextureType::DEPTH);

		}

		RenderPassDesc renderPassDesc	= RenderPassDesc();
		renderPassDesc.AttachmentCount	= u32(attachments.size());
		renderPassDesc.AttachmentTypes	= attachmentTypes.data();
		renderPassDesc.Attachments		= attachments.data();
		renderPassDesc.SwapChainTarget	= m_PipelineInfo.SwapChainTarget;
		renderPassDesc.Clear			= m_PipelineInfo.ClearTargets;

		RenderPass* renderPass = RenderPass::Create(renderPassDesc);

		FrameBufferDesc frameBufferInfo = FrameBufferDesc();
		frameBufferInfo.Size = Vector2u(1000, 1000);
		frameBufferInfo.AttachmentCount = u32(attachments.size());
		frameBufferInfo.RenderPass = renderPass;
		frameBufferInfo.AttachmentTypes = attachmentTypes.data();

		if (m_PipelineInfo.SwapChainTarget)
		{
			for(u32 i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
			{
				attachments[0] = RendererCommand::GetMainSwapChain()->GetImage(i);
				frameBufferInfo.ScreenFBO = true;
				frameBufferInfo.Attachments = attachments.data();
				m_FrameBuffer.emplace_back(FrameBuffer::Create(frameBufferInfo));
			}
		}

	}

	void VulkanPipeline::TransitionBackbuffers()
	{
		auto commandBuffer = RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer();
		if (m_PipelineInfo.SwapChainTarget)
		{
			for (u32 i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
				static_cast<VulkanTexture2D*>(RendererCommand::GetMainSwapChain()->GetImage(i))->TransitionImage(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer() );
		}

		if (m_PipelineInfo.DepthTarget)
		{
			static_cast<VulkanTextureDepth*>(m_PipelineInfo.DepthTarget)->TransitionImage(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());

		}
	}
}