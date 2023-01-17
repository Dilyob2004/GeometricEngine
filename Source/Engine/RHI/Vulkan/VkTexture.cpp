#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/ImageCore.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/Render/ImageLoader.h>
#include <Engine/Render/Vulkan/VkBuffer.h>
namespace MeteorEngine
{


	VkSamplerAddressMode TextureWrapToVK(const TextureWrap wrap)
	{
		switch (wrap)
		{
		case TextureWrap::CLAMP:
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			//case TextureWrap::CLAMP_TO_BORDER:
				//return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		case TextureWrap::CLAMP_TO_EDGE:
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:
			return VK_SAMPLER_ADDRESS_MODE_REPEAT;
			//case TextureWrap::MIRRORED_REPEAT:
				//return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		default:
			LOG("[Texture] Unsupported wrap type!");
			return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		}
	}

	VkFilter TextureFilterToVK(const TextureFilter filter)
	{
		switch (filter)
		{
		case TextureFilter::NEAREST:
			return VK_FILTER_NEAREST;
		case TextureFilter::LINEAR:
			return VK_FILTER_LINEAR;
		case TextureFilter::NONE:
			return VK_FILTER_LINEAR;
		default:
			LOG("[Texture] Unsupported TextureFilter type!");
			return VK_FILTER_LINEAR;
		}
	}
	VkImageView CreateImageViews(	VkDevice device, 
									VkImage image, 
									VkFormat format, 
									u32 mipLevels, 
									VkImageViewType viewType,
									VkImageAspectFlags aspectMask, 
									u32 layerCount, 
									u32 baseArrayLayer = 0, 
									u32 baseMipLevel = 0)
	{

		VkImageViewCreateInfo imageViewCreateInfo = VkImageViewCreateInfo();
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.image = image;
		imageViewCreateInfo.viewType = viewType;
		imageViewCreateInfo.format = format;
		imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		imageViewCreateInfo.subresourceRange.aspectMask = aspectMask;
		imageViewCreateInfo.subresourceRange.baseMipLevel = baseMipLevel;
		imageViewCreateInfo.subresourceRange.levelCount = mipLevels;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = baseArrayLayer;
		imageViewCreateInfo.subresourceRange.layerCount = layerCount;
		VkImageView imageView;
		if (vkCreateImageView(device, &imageViewCreateInfo, 0, &imageView) != VK_SUCCESS)
		{
			LOG("Failed to create Texture View");
			return 0;
		}

		return imageView;
	}

	VkSampler CreateTextureSampler(	VkDevice device, 
									VkFilter magFilter = VK_FILTER_LINEAR, 
									VkFilter minFilter = VK_FILTER_LINEAR, 
									f32 minLod = 0.0f, 
									f32 maxLod = 1.0f, 
									bool anisotropyEnable = false, 
									f32 maxAnisotropy = 1.0f, 
									VkSamplerAddressMode modeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
									VkSamplerAddressMode modeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
									VkSamplerAddressMode modeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE)
	{
		VkSamplerCreateInfo samplerInfo = VkSamplerCreateInfo();
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = magFilter;
		samplerInfo.minFilter = minFilter;
		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerInfo.addressModeU = modeU;
		samplerInfo.addressModeV = modeV;
		samplerInfo.addressModeW = modeW;
		samplerInfo.maxAnisotropy = maxAnisotropy;
		samplerInfo.anisotropyEnable = anisotropyEnable;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerInfo.minLod = minLod;
		samplerInfo.maxLod = maxLod;

		VkSampler sampler;
		if (vkCreateSampler(device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS)
			LOG("Failed to create texture sampler!");

		return sampler;
	}
	VulkanTexture2D::VulkanTexture2D()
	{

	}	
	void VulkanTexture2D::Load()
	{
		std::vector<u8> Pointer;
		m_Flags |= TextureFlags::Texture_Sampled;
		s32 Bits = 0;
		if (m_Pointer == NULL)
		{
			m_DeleteImage = ImageLoader::Load(m_Path, Pointer, m_Size, Bits);
			m_Pointer = Pointer.data();


			switch (Bits)
			{
			case 8:
				m_Format = RHIPixelFormat::R8_UNORM;
				break;
			case 16:
				m_Format = RHIPixelFormat::RG8_UNORM;
				break;
			case 24:
				m_Format = RHIPixelFormat::RGB8_UNORM;
				break;
			case 32:
				m_Format = RHIPixelFormat::RGBA8_UNORM;
				break;
			case 48:
				m_Format = RHIPixelFormat::RGB16_F32;
				break;
			case 64:
				m_Format = RHIPixelFormat::RGBA16_F32;
				break;
			case 96:
				m_Format = RHIPixelFormat::RGB32_F32;
				break;
			case 128:
				m_Format = RHIPixelFormat::RGBA32_F32;
				break;
			default:
				m_Format = RHIPixelFormat::RGBA8_UNORM;
				break;
			}
		}
		else
		{
			u32 newBits = 0;
			switch (m_Parameters.Format)
			{
			case RHIPixelFormat::R8_UNORM:
				newBits = 8;
				break;
			case RHIPixelFormat::RG8_UNORM:
				newBits = 16;
				break;
			case RHIPixelFormat::RGB8_UNORM:
				newBits = 24;
				break;
			case RHIPixelFormat::RGBA8_UNORM:
				newBits = 32;
				break;
			case RHIPixelFormat::RGB16_F32:
				newBits = 48;
				break;
			case RHIPixelFormat::RGBA16_F32:
				newBits = 64;
				break;
			case RHIPixelFormat::RGB32_F32:
				newBits = 96;
				break;
			case RHIPixelFormat::RGBA32_F32:
				newBits = 128;
				break;
			default:
				m_Format = RHIPixelFormat::RGBA8_UNORM;
				newBits = 32;
				break;
			}
			Bits = newBits;
		}
		m_VKFormat = (RHIPixelFormatToVK(m_Parameters.Format, m_Parameters.IsSRGB));

		VkDeviceSize imageSize = VkDeviceSize(m_Size.x * m_Size.y * Bits / 8);

		if (!m_Pointer)
			LOG("Failed to load texture image!");

		m_MipLevels = static_cast<u32>(std::floor(std::log2(max(m_Size.x, m_Size.y)))) + 1;

		if (!(m_Flags & TextureFlags::Texture_CreateMips))
			m_MipLevels = 1;
		VulkanBuffer * stagingBuffer = new VulkanBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, static_cast<u32>(imageSize), m_Pointer);


		CreateImage(VulkanDevice::GetInstance()->GetLogicalDevice(),
			VulkanDevice::GetInstance()->GetPhysicalDevice(),
			m_Size.x, m_Size.y,
			m_MipLevels, m_VKFormat,
			VK_IMAGE_TYPE_2D,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
			VK_IMAGE_USAGE_TRANSFER_DST_BIT |
			VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_Image,
			m_ImageMemory, 1, 0);

		TransitionImageLayout(VulkanDevice::GetInstance()->GetLogicalDevice(),
			VulkanDevice::GetInstance()->GetQueue(),
			VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(),
			m_Image, m_VKFormat, VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_MipLevels, 0, NULL);
		CopyBufferToImage(VulkanDevice::GetInstance()->GetLogicalDevice(),
			VulkanDevice::GetInstance()->GetQueue(),
			VulkanDevice::GetInstance()->GetCommandPool()->GetCommandPool(),
			stagingBuffer->GetBuffer(), m_Image,
			static_cast<u32>(m_Size.x), static_cast<u32>(m_Size.y));

		delete stagingBuffer;
		TransitionImage(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	}
	VulkanTexture2D::VulkanTexture2D(const std::string& path, const TextureDesc& desc) :
		m_Parameters(desc),
		m_Path(path),
		m_DeleteImage(true)
	{
		Load();
		m_ImageView = CreateImageViews(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, m_VKFormat, 1,
			VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		m_Sampler = CreateTextureSampler(VulkanDevice::GetInstance()->GetLogicalDevice(),
			TextureFilterToVK(m_Parameters.MinFilter),
			TextureFilterToVK(m_Parameters.MagFilter),
			0.0f, static_cast<f32>(m_MipLevels), false, VulkanDevice::GetInstance()->GetProperties().limits.maxSamplerAnisotropy,
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode));
		UpdateDescriptor();
	}
	VulkanTexture2D::VulkanTexture2D(const TextureDesc& desc, const Vector2u& size):
		m_Size(size),
		m_DeleteImage(true),
		m_Parameters(desc),
		m_Format(desc.Format),
		m_VKFormat(RHIPixelFormatToVK(desc.Format, desc.IsSRGB))
	{
		m_Flags = desc.Flags;
		BuildTexture();
	}	
	VulkanTexture2D::VulkanTexture2D(const TextureDesc& desc, const Vector2u& size, void* pixels):
		m_Size(size),
		m_DeleteImage(true),
		m_Parameters(desc),
		m_Format(desc.Format),
		m_VKFormat(RHIPixelFormatToVK(desc.Format, desc.IsSRGB)),
		m_Pointer(static_cast<u8*>(pixels))
	{
		m_Flags = desc.Flags;
		Load();
		m_ImageView = CreateImageViews(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, m_VKFormat, 1,
			VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		m_Sampler = CreateTextureSampler(VulkanDevice::GetInstance()->GetLogicalDevice(),
			TextureFilterToVK(m_Parameters.MinFilter),
			TextureFilterToVK(m_Parameters.MagFilter),
			0.0f, static_cast<f32>(m_MipLevels), false, VulkanDevice::GetInstance()->GetProperties().limits.maxSamplerAnisotropy,
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode),
			TextureWrapToVK(m_Parameters.WrapMode));
		UpdateDescriptor();
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


	VkImageView VulkanTexture2D::GetMipImageView(u32 mip)
	{
		if (m_MipImageViews.find(mip) == m_MipImageViews.end())
			m_MipImageViews[mip] = CreateImageViews(VulkanDevice::GetInstance()->GetLogicalDevice(), m_Image, m_VKFormat, 1, VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, 1, 0, mip);
		return m_MipImageViews.at(mip);
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