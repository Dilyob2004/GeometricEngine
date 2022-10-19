#include <Engine/Render/Vulkan/VkRenderer.h>

namespace MeteorEngine
{
	VkDescriptorPool VulkanRenderer::s_DescriptorPool = {};
	VulkanRenderer::VulkanRenderer():
		m_SwapChain(0)
	{
		m_DescriptorCapacity = 1024;
	}
	VulkanRenderer::~VulkanRenderer()
	{

	}
	void VulkanRenderer::Init(RenderContext* context, const Vector2u& size, bool vsync)
	{
		m_SwapChain = new VulkanSwapChain();
		m_SwapChain->Create((VulkanContext*)context, size, vsync);

		// Pool sizes
		std::vector<VkDescriptorPoolSize> poolSizes;
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_SAMPLER, 1024 });
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1024 });
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1024 });
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1024 });
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1024 });
		poolSizes.push_back({ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1024 });

		VkDescriptorPoolSize pool_sizes[] = {
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 100000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 100000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 100000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 100000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 100000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 100000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 100000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 100000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 100000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 100000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 100000 }
		};
		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 100000 * 11;
		pool_info.poolSizeCount = (uint32_t)11;
		pool_info.pPoolSizes = pool_sizes;

		// Create info
		VkDescriptorPoolCreateInfo poolCreateInfo = {};
		poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		poolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolCreateInfo.pPoolSizes = poolSizes.data();
		poolCreateInfo.maxSets = m_DescriptorCapacity;

		// Pool
		vkCreateDescriptorPool(VulkanDevice::GetInstance()->GetLogicalDevice(), &pool_info, nullptr, &s_DescriptorPool);
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