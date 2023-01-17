#include <Engine/Render/Vulkan/VkRenderer.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Vulkan/VkPipeline.h>
#include <Engine/Render/Vulkan/VkDescriptorSet.h>

namespace MeteorEngine
{
	VkDescriptorPool VulkanRenderer::s_DescriptorPool = {};
	VulkanRenderer::VulkanRenderer():
		m_SwapChain(NULL)
	{
		m_DescriptorCapacity = 1024;
	}
	VulkanRenderer::~VulkanRenderer()
	{

	}
	void VulkanRenderer::ClearRenderTarget(Texture* texture, CommandBuffer* commandBuffer, const Vector4f& clearColour)
	{
		VkImageSubresourceRange subresourceRange = {}; // TODO: Get from texture
		subresourceRange.baseMipLevel = 0;
		subresourceRange.layerCount = 1;
		subresourceRange.levelCount = 1;
		subresourceRange.baseArrayLayer = 0;

		if (texture->GetType() == TextureType::COLOR)
		{
			VkImageLayout layout = ((VulkanTexture2D*)texture)->GetImageLayout();
			((VulkanTexture2D*)texture)->TransitionImage(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());

			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

			VkClearColorValue clearColourValue = VkClearColorValue({ { clearColour.x, clearColour.y, clearColour.z, clearColour.w } });
			vkCmdClearColorImage(((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer(), 
				static_cast<VulkanTexture2D*>(texture)->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColourValue, 1, &subresourceRange);
			((VulkanTexture2D*)texture)->TransitionImage(layout, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());
		}
		else if (texture->GetType() == TextureType::DEPTH)
		{
			VkClearDepthStencilValue clear_depth_stencil = { 1.0f, 1 };

			subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
			((VulkanTextureDepth*)texture)->TransitionImage(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer());
			vkCmdClearDepthStencilImage(((VulkanCommandBuffer*)commandBuffer)->GetCommandBuffer(), 
				static_cast<VulkanTextureDepth*>(texture)->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clear_depth_stencil, 1, &subresourceRange);
		}
	}
	void VulkanRenderer::BindDescriptorSets(Pipeline* pipeline, CommandBuffer* commandBuffer, u32 dynamicOffset, DescriptorSet** descriptorSets, u32 descriptorCount)
	{
		u32 numDynamicDescriptorSets = 0, numDesciptorSets = 0;

		for (u32 i = 0; i < descriptorCount; i++)
		{
			if (descriptorSets[i])
			{
				auto vkDesSet = static_cast<VulkanDescriptorSet*>(descriptorSets[i]);
				if (vkDesSet->IsDynamic())
					numDynamicDescriptorSets++;

				m_DescriptorSetPool[numDesciptorSets] = vkDesSet->GetDescriptorSet();

				//LUMOS_ASSERT(vkDesSet->GetHasUpdated(Renderer::GetMainSwapChain()->GetCurrentBufferIndex()), "Descriptor Set has not been updated before");
				numDesciptorSets++;
			}
		}

		vkCmdBindDescriptorSets(static_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), /*static_cast<VulkanPipeline*>(pipeline)->IsCompute() ? VK_PIPELINE_BIND_POINT_COMPUTE :*/ VK_PIPELINE_BIND_POINT_GRAPHICS, static_cast<VulkanPipeline*>(pipeline)->GetPipelineLayout(), 0, numDesciptorSets, m_DescriptorSetPool, numDynamicDescriptorSets, &dynamicOffset);


	}


	void VulkanRenderer::DrawIndexed(CommandBuffer* commandBuffer, DrawType type, u32 count, u32 start) const
	{
		vkCmdDraw(static_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), count, 1, 0, 0);
	}
	void VulkanRenderer::ClearSwapChainImages() const
	{
		for (int i = 0; i < m_SwapChain->GetSwapChainBufferCount(); i++)
		{
			auto cmd = BeginSingleTimeCommands(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool());

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.layerCount = 1;
			subresourceRange.levelCount = 1;

			VkClearColorValue clearColourValue{ { 0.07f, 0.07f,0.05f, 1.f } };

			vkCmdClearColorImage(cmd, dynamic_cast<VulkanTexture2D*>(m_SwapChain->GetImage(i))->GetImage(), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, &clearColourValue, 1, &subresourceRange);

			EndSingleTimeCommands(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetQueue(),VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(), cmd);
		}
	}
	void VulkanRenderer::Init(RenderContext* context, const Vector2u& size, bool vsync)
	{
		m_SwapChain = SwapChain::Create(context, size, vsync);

		// Pool sizes

		{
			VkDescriptorPoolSize pool_sizes[] = {
				{ VK_DESCRIPTOR_TYPE_SAMPLER, 10000 },
				{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 10000 },
				{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 10000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 10000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 10000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 10000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 10000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 10000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 10000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 10000 },
				{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 10000 }
			};
			VkDescriptorPoolCreateInfo pool_info = {};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
			pool_info.maxSets = 10000 * 11;
			pool_info.poolSizeCount = (u32)11;
			pool_info.pPoolSizes = pool_sizes;


			// Pool
			vkCreateDescriptorPool(VulkanDevice::GetInstance()->GetLogicalDevice(), &pool_info, nullptr, &s_DescriptorPool);
		}
	}
	void VulkanRenderer::Begin()
	{
		m_SwapChain->Begin();
	}
	void VulkanRenderer::Resize(const Vector2u& size)
	{
		m_SwapChain->Resize(size);
	}
	void VulkanRenderer::Present()
	{
		m_SwapChain->End();

		m_SwapChain->QueueSubmit();
		m_SwapChain->Present();
	}
}