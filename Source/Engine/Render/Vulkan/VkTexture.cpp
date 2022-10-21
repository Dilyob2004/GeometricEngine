#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
namespace MeteorEngine
{

	VulkanTexture2D::VulkanTexture2D()
	{

	}	
	VulkanTexture2D::VulkanTexture2D(const TextureDesc& parametes, const Vector2u& size):
		m_Size(size),
		m_DeleteImage(true),
		m_Parameters(parametes),
		m_Format(parametes.Format),
		m_VKFormat(RHIPixelFormatToVK(parametes.Format, parametes.IsSRGB))
	{
		BuildTexture();
	}
	VulkanTexture2D::VulkanTexture2D(VkImage image, VkImageView imageView, VkFormat format, const Vector2u& size) :
		m_Image(image), 
		m_ImageView(imageView) , 
		m_Sampler(VK_NULL_HANDLE), 
		m_Size(size), 
		m_VKFormat(format), 
		m_DeleteImage(false),
		m_ImageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
	{
		m_ImageMemory = VK_NULL_HANDLE;
		UpdateDescriptor();
	}
	VulkanTexture2D::~VulkanTexture2D()
	{
		Cleanup();
	}
	void VulkanTexture2D::BuildTexture()
	{

		if (m_Flags & TextureFlags::Texture_CreateMips)
			m_MipLevels = static_cast<u32>(std::floor(std::log2(max(m_Size.x, m_Size.y)))) + 1;
		CreateImage(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetPhysicalDevice(),
			m_Size.x, m_Size.y, m_MipLevels, m_VKFormat, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_Image, m_ImageMemory, 1, 0);

		m_ImageView = CreateImageViews(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, m_VKFormat, m_MipLevels,
			VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, 1);

		m_Sampler = CreateTextureSampler(VulkanDevice::GetInstance()->GetLogicalDevice(),
			TextureFilterToVK(m_Parameters.MinFilter),
			TextureFilterToVK(m_Parameters.MagFilter),
			0.0f, static_cast<f32>(m_MipLevels), false, VulkanDevice::GetInstance()->GetProperties().limits.maxSamplerAnisotropy,
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode));

		m_ImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		TransitionImage(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
		UpdateDescriptor();
	}
	void VulkanTexture2D::Cleanup()
	{
		if(m_Sampler)
			vkDestroySampler(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Sampler, NULL);

		if(m_ImageView)
			vkDestroyImageView(VulkanDevice::GetInstance()->GetLogicalDevice(), m_ImageView, NULL);


		if (m_DeleteImage) {
			vkDestroyImage(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, NULL);
			vkFreeMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_ImageMemory, NULL);
		}
	}
	void VulkanTexture2D::Resize(const Vector2u& size)
	{
		Cleanup();
		m_Size = size;
		m_Image = VkImage();
		BuildTexture();
	}
	void VulkanTexture2D::TransitionImage(VkImageLayout newLayout, VkCommandBuffer commandBuffer)
	{
		
		if (newLayout != m_ImageLayout)
			TransitionImageLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetQueue(), VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(), m_Image, m_VKFormat, m_ImageLayout, newLayout, m_MipLevels, 1, commandBuffer);
		m_ImageLayout = newLayout;
		UpdateDescriptor();
	}




	VulkanTextureDepth::VulkanTextureDepth(){}
	VulkanTextureDepth::VulkanTextureDepth(const Vector2u& size):
		m_Size(size)
	{
		VkFormat format = FindDepthFormat(VulkanDevice::GetInstance()->GetPhysicalDevice());
		m_VKFormat = format;
		m_Format = VKToFormat(m_VKFormat);
		BuildTexture();
	}
	void VulkanTextureDepth::Resize(const Vector2u& size)
	{
		Cleanup();
		m_Size = size;
		m_Image = VkImage();
		BuildTexture();
	}
	void VulkanTextureDepth::TransitionImage(VkImageLayout newLayout, VkCommandBuffer commandBuffer)
	{

		if (newLayout != m_ImageLayout)
			TransitionImageLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), 
				VulkanDevice::GetInstance()->GetQueue(), 
				VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(), 
				m_Image, m_VKFormat, m_ImageLayout, newLayout, 1, 1, commandBuffer);
		m_ImageLayout = newLayout;
		UpdateDescriptor();
	}
	void VulkanTextureDepth::Cleanup()
	{
		if (m_Sampler)
			vkDestroySampler(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Sampler, NULL);

		if (m_ImageView)
			vkDestroyImageView(VulkanDevice::GetInstance()->GetLogicalDevice(), m_ImageView, NULL);


		if (m_Image) {
			vkDestroyImage(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, NULL);
			vkFreeMemory(VulkanDevice::GetInstance()->GetLogicalDevice(), m_ImageMemory, NULL);
		}
	}
	VulkanTextureDepth::~VulkanTextureDepth()
	{
		Cleanup();
	}
	void VulkanTextureDepth::BuildTexture()
	{
		CreateImage(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetPhysicalDevice(),
			m_Size.x, m_Size.y, 1, m_VKFormat, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, 
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_Image, m_ImageMemory, 1, 0);

		m_ImageView = CreateImageViews(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, m_VKFormat, 1,
			VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_DEPTH_BIT, 1);

		TransitionImageLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), VulkanDevice::GetInstance()->GetQueue(),
			VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(),
			
			m_Image, m_VKFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1, 1, NULL);

		m_ImageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


		m_Sampler = CreateTextureSampler(VulkanDevice::GetInstance()->GetLogicalDevice(), 
			VK_FILTER_LINEAR, VK_FILTER_LINEAR, 0.0f, 1.0f,
			false, VulkanDevice::GetInstance()->GetProperties().limits.maxSamplerAnisotropy,
			VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
			VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
			VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE);

		m_Flags |= TextureFlags::Texture_DepthStencil;

		UpdateDescriptor();
	}
}