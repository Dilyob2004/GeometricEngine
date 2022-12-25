#include <Engine/Render/Vulkan/VkPipeline.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkRenderPass.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkShader.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/Core/Application.h>

namespace MeteorEngine
{
	VulkanPipeline::VulkanPipeline():
		m_Shader(0),
		m_PipelineLayout(0),
		m_Pipeline(0),
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
		m_Shader = pipelineInfo.PipelineShader;
		m_PipelineLayout = ((VulkanShader*)m_Shader)->GetPipelineLayout();
		TransitionBackbuffers();
		std::vector<VkDynamicState> dynamicStateDescriptors;
		VkPipelineDynamicStateCreateInfo dynamicStateCI = VkPipelineDynamicStateCreateInfo();
		dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCI.pNext = NULL;
		dynamicStateCI.pDynamicStates = dynamicStateDescriptors.data();
		///Not Compute
		std::vector<VkVertexInputAttributeDescription> vertexInputDescription;
		PreInit();

		u32 stride = ((VulkanShader*)m_Shader)->GetVertexInputStride();

		// Vertex layout
		VkVertexInputBindingDescription vertexBindingDescription;

		if (stride > 0)
		{
			vertexBindingDescription.binding = 0;
			vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			vertexBindingDescription.stride = stride;
		}


		const std::vector<VkVertexInputAttributeDescription>& vertexInputAttributeDescription = ((VulkanShader*)m_Shader)->GetVertexInputAttributeDescription();

		VkPipelineVertexInputStateCreateInfo vi = VkPipelineVertexInputStateCreateInfo();
		vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vi.pNext = NULL;
		vi.vertexBindingDescriptionCount = stride > 0 ? 1 : 0;
		vi.pVertexBindingDescriptions = stride > 0 ? &vertexBindingDescription : nullptr;
		vi.vertexAttributeDescriptionCount = stride > 0 ? u32(vertexInputAttributeDescription.size()) : 0;
		vi.pVertexAttributeDescriptions = stride > 0 ? vertexInputAttributeDescription.data() : nullptr;

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyCI = VkPipelineInputAssemblyStateCreateInfo();
		inputAssemblyCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyCI.pNext = NULL;
		inputAssemblyCI.primitiveRestartEnable = VK_FALSE;
		inputAssemblyCI.topology = DrawTypeToVk(pipelineInfo.drawType);

		VkPipelineRasterizationStateCreateInfo rs = VkPipelineRasterizationStateCreateInfo();
		rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rs.polygonMode = PolygonModeToVk(pipelineInfo.polygonMode);
		rs.cullMode = CullModeToVK(pipelineInfo.cullMode);
		rs.frontFace = pipelineInfo.SwapChainTarget ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
		rs.depthClampEnable = VK_FALSE;
		rs.rasterizerDiscardEnable = VK_FALSE;
		rs.depthBiasEnable = (pipelineInfo.DepthBiasEnabled ? VK_TRUE : VK_FALSE);
		rs.depthBiasConstantFactor = pipelineInfo.DepthBiasConstantFactor;
		rs.depthBiasClamp = 0;
		rs.depthBiasSlopeFactor = pipelineInfo.DepthBiasSlopeFactor;
		rs.lineWidth = 1.0f;
		rs.pNext = NULL;
		VkPipelineColorBlendStateCreateInfo cb = VkPipelineColorBlendStateCreateInfo();
		cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		cb.pNext = NULL;
		cb.flags = 0;
		std::vector<VkPipelineColorBlendAttachmentState> blendAttachState;
		blendAttachState.resize(((VulkanRenderPass*)m_RenderPass)->GetAttachmentCount());
		for (u32 i = 0; i < blendAttachState.size(); i++)
		{
			blendAttachState[i] = VkPipelineColorBlendAttachmentState();
			blendAttachState[i].colorWriteMask = 0x0f;
			blendAttachState[i].alphaBlendOp = VK_BLEND_OP_ADD;
			blendAttachState[i].colorBlendOp = VK_BLEND_OP_ADD;

			if (pipelineInfo.TransparencyEnabled)
			{
				blendAttachState[i].blendEnable = VK_TRUE;
				blendAttachState[i].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
				blendAttachState[i].dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;

				if (pipelineInfo.blendMode == BlendMode::SrcAlphaOneMinusSrcAlpha)
				{
					blendAttachState[i].srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
					blendAttachState[i].dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
				}
				else if (pipelineInfo.blendMode == BlendMode::ZeroSrcColor)
				{
					blendAttachState[i].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
					blendAttachState[i].dstColorBlendFactor = VK_BLEND_FACTOR_SRC_COLOR;
				}
				else if (pipelineInfo.blendMode == BlendMode::OneZero)
				{
					blendAttachState[i].srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
					blendAttachState[i].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
				}
				else
				{
					blendAttachState[i].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
					blendAttachState[i].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
				}
			}
			else
			{
				blendAttachState[i].blendEnable = VK_FALSE;
				blendAttachState[i].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
				blendAttachState[i].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
				blendAttachState[i].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
				blendAttachState[i].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			}
		}

		cb.attachmentCount = static_cast<u32>(blendAttachState.size());
		cb.pAttachments = blendAttachState.data();
		cb.logicOpEnable = VK_FALSE;
		cb.logicOp = VK_LOGIC_OP_NO_OP;
		cb.blendConstants[0] = 1.0f;
		cb.blendConstants[1] = 1.0f;
		cb.blendConstants[2] = 1.0f;
		cb.blendConstants[3] = 1.0f;

		VkPipelineViewportStateCreateInfo vp = VkPipelineViewportStateCreateInfo();
		vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		vp.pNext = NULL;
		vp.viewportCount = 1;
		vp.scissorCount = 1;
		vp.pScissors = NULL;
		vp.pViewports = NULL;
		dynamicStateDescriptors.push_back(VK_DYNAMIC_STATE_VIEWPORT);
		dynamicStateDescriptors.push_back(VK_DYNAMIC_STATE_SCISSOR);


		if (pipelineInfo.DepthBiasEnabled)
		{
			dynamicStateDescriptors.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS);
			m_DepthBiasConstant = pipelineInfo.DepthBiasConstantFactor;
			m_DepthBiasSlope = pipelineInfo.DepthBiasSlopeFactor;
			m_DepthBiasEnabled = true;
		}
		else
		{
			m_DepthBiasEnabled = false;
		}


		VkPipelineDepthStencilStateCreateInfo ds = VkPipelineDepthStencilStateCreateInfo();
		ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		ds.pNext = NULL;
		ds.depthTestEnable = VK_TRUE;
		ds.depthWriteEnable = VK_TRUE;
		ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		ds.depthBoundsTestEnable = VK_FALSE;
		ds.stencilTestEnable = VK_FALSE;
		ds.back.failOp = VK_STENCIL_OP_KEEP;
		ds.back.passOp = VK_STENCIL_OP_KEEP;
		ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
		ds.back.compareMask = 0;
		ds.back.reference = 0;
		ds.back.depthFailOp = VK_STENCIL_OP_KEEP;
		ds.back.writeMask = 0;
		ds.minDepthBounds = 0;
		ds.maxDepthBounds = 0;
		ds.front = ds.back;

		VkPipelineMultisampleStateCreateInfo ms = VkPipelineMultisampleStateCreateInfo();
		ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		ms.pNext = NULL;
		ms.pSampleMask = NULL;
		ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		ms.sampleShadingEnable = VK_FALSE;
		ms.alphaToCoverageEnable = VK_FALSE;
		ms.alphaToOneEnable = VK_FALSE;
		ms.minSampleShading = 0.0;

		dynamicStateCI.dynamicStateCount = u32(dynamicStateDescriptors.size());
		dynamicStateCI.pDynamicStates = dynamicStateDescriptors.data();

		auto vkshader = (VulkanShader*)pipelineInfo.PipelineShader;
		VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = VkGraphicsPipelineCreateInfo();
		graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		graphicsPipelineCreateInfo.pNext = NULL;
		graphicsPipelineCreateInfo.layout = m_PipelineLayout;
		graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineCreateInfo.basePipelineIndex = -1;
		graphicsPipelineCreateInfo.pVertexInputState = &vi;
		graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssemblyCI;
		graphicsPipelineCreateInfo.pRasterizationState = &rs;
		graphicsPipelineCreateInfo.pColorBlendState = &cb;
		graphicsPipelineCreateInfo.pTessellationState = VK_NULL_HANDLE;
		graphicsPipelineCreateInfo.pMultisampleState = &ms;
		graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCI;
		graphicsPipelineCreateInfo.pViewportState = &vp;
		graphicsPipelineCreateInfo.pDepthStencilState = &ds;
		graphicsPipelineCreateInfo.pStages = vkshader->GetShaderStages();
		graphicsPipelineCreateInfo.stageCount = vkshader->GetStageCount();
		graphicsPipelineCreateInfo.renderPass = ((VulkanRenderPass*)m_RenderPass)->GetRenderPass();
		graphicsPipelineCreateInfo.subpass = 0;
		vkCreateGraphicsPipelines(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetPipelineCache(), 1, &graphicsPipelineCreateInfo, VK_NULL_HANDLE, &m_Pipeline);

	}
	VulkanPipeline::~VulkanPipeline()
	{
		vkDestroyPipeline(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Pipeline, VK_NULL_HANDLE);
	}
	void VulkanPipeline::Begin(CommandBuffer* commandBuffer)
	{
		FrameBuffer* frameBuffer = NULL;
		if (true)
		{
			TransitionBackbuffers();
			if (m_PipelineInfo.SwapChainTarget)
				frameBuffer = m_FrameBuffer[RendererCommand::GetMainSwapChain()->GetCurrentImageIndex()];
			else
				frameBuffer = m_FrameBuffer[0];
			m_RenderPass->BeginRenderpass(commandBuffer, m_PipelineInfo.clearColor, frameBuffer, 
				SubPassContents::INLINE, { Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight() });

		}
		else
			commandBuffer->UpdateViewport({ Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight() }, false);

		vkCmdBindPipeline(static_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(),  VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);

		// Bug in moltenVK. Needs to happen after pipeline bound for now.
		if (m_DepthBiasEnabled)
			vkCmdSetDepthBias(static_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(),
				m_DepthBiasConstant,
				0.0f,
				m_DepthBiasSlope);
	}
	void VulkanPipeline::End(CommandBuffer* commandBuffer)
	{
		m_RenderPass->EndRenderpass(commandBuffer);
	}

	void VulkanPipeline::ClearRenderTargets(CommandBuffer* commandBuffer)
	{

		if (m_PipelineInfo.SwapChainTarget)
			for (u32 i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
				RendererCommand::ClearRenderTarget(RendererCommand::GetMainSwapChain()->GetImage(i), commandBuffer);
		if (m_PipelineInfo.DepthTarget)
			RendererCommand::ClearRenderTarget(m_PipelineInfo.DepthTarget, commandBuffer);



		/**{
			for (auto texture : m_PipelineInfo.ColorTargets)
			{
				if (texture != NULL)
					RendererCommand::ClearRenderTarget(texture, commandBuffer);
			}
		}*/
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
		/**else {
			for (auto texture : m_PipelineInfo.ColorTargets)
				if (texture)
				{
					attachments.push_back(texture);
					attachmentTypes.push_back(texture->GetType());
				}
		}*/
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

		m_RenderPass = RenderPass::Create(renderPassDesc);
		FrameBufferDesc frameBufferInfo = FrameBufferDesc();
		frameBufferInfo.Size = Vector2u(Application::GetInstance().GetWidth(), Application::GetInstance().GetHeight());
		frameBufferInfo.AttachmentCount = u32(attachments.size());
		frameBufferInfo.RenderPass = m_RenderPass;
		frameBufferInfo.AttachmentTypes = attachmentTypes.data();

		if (m_PipelineInfo.SwapChainTarget)
			for(u32 i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
			{
				attachments[0] = RendererCommand::GetMainSwapChain()->GetImage(i);
				frameBufferInfo.ScreenFBO = true;
				frameBufferInfo.Attachments = attachments.data();
				m_FrameBuffer.emplace_back(FrameBuffer::Create(frameBufferInfo));
			}

	}

	void VulkanPipeline::TransitionBackbuffers()
	{
		auto commandBuffer = RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer();
		if (m_PipelineInfo.SwapChainTarget)
			for (u32 i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
				static_cast<VulkanTexture2D*>(RendererCommand::GetMainSwapChain()->GetImage(i))->TransitionImage(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer() );

		if (m_PipelineInfo.DepthTarget)
			static_cast<VulkanTextureDepth*>(m_PipelineInfo.DepthTarget)->TransitionImage(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());
	}
}